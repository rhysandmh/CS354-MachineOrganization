#include "mem.h"
extern BLOCK_HEADER* first_header;

//--Helper Function--

/* This function takes a block header as input and checks to see if 
 * it is the last block i.e. checks if the header's size_alloc data is equal to 1. 
 * It returns 1 if the provided block header is the last block and 0 otherwise.
 */
int Is_Last(BLOCK_HEADER* block_header){
	if(block_header->size_alloc == 1){
		return 1;
	}
	return 0;
}

/* This function takes a block header as input and checks to see 
 * if it has been allocated. If it has been allocated it returns 1,
 * if it is free it returns 0.
 */
int Not_Free(BLOCK_HEADER* block_header){
	if(block_header->size_alloc % 2 == 0){
		return 0;
	}	
	return 1;
}

/* This function takes a block header as input and returns a pointer to the first address
 * the payload. 
 */
void* Get_User_Pointer(BLOCK_HEADER* block_header){
	return (void*)(8 + (unsigned long) block_header);
}

/* This function takes a block header and it's size as input and returns a pointer to the 
 * next block header 
 */
void* Get_Next_Header(BLOCK_HEADER* block_header, int sizeOf){
	return (BLOCK_HEADER*)(sizeOf + (unsigned long) block_header);
}

/* This function takes a block header and returns its size.
 */
int Get_Size(BLOCK_HEADER* block_header){
	if(Not_Free(block_header)){
		return block_header->size_alloc - 1;
	}
	return block_header->size_alloc;
}

/* This function takes a block header and returns the size of its padding.
 */
int Get_Padding(BLOCK_HEADER* block_header){
	return Get_Size(block_header) - block_header->payload - 8;
}

/* This function takes a block header as input and sets it to allocated if it is currently
 * free and does nothing otherwise.
 */
void Set_Allocated(BLOCK_HEADER* block_header){
	if(!Not_Free(block_header)){
		block_header->size_alloc += 1;
	}
}

/* This function takes a block header as input and sets it to free if it is currently
 * allocated and does nothing otherwise.
 */
void Set_Free(BLOCK_HEADER* block_header){
	if(Not_Free(block_header)){
		block_header->size_alloc -= 1;
	}	
}


// return a pointer to the payload
// if a large enough free block isn't available, return NULL
void* Mem_Alloc(int size){
	
	//LOCAL VARIABLES
    BLOCK_HEADER *retVal;
	BLOCK_HEADER *current = first_header;
    int payload = 0;
	int block_size = 0;
    int padding_size = 0;

 	// 1.1 find a free block that's big enough
	// Hint: MEM_DUMP goes through all the blocks and prints them out
	//

	// While the current is not the last block
	while(!Is_Last(current)){
		//Compute the Block Size
		block_size = Get_Size(current);
		//Initialize the retVal local variable to be a pointer to the first element in the payload
		retVal = Get_User_Pointer(current);
		//Initialize local variable to the payload size of the current block header
		payload = current->payload;
	
	// 1.2 allocate the block
	//
		//If the current block is free and the size passed to the function fits within the payload	
		if( (size <= (block_size-8)) && (!Not_Free(current))){
			//Set the size_alloc data in the Block Header to allocated
			Set_Allocated(current);			
			
	// 1.3 split if necessary (if padding size is greater than or equal to 16 split the block)
	//
			//If the payload size is greater than or equal to 16
			if(payload >= 16){
				//Calculate the padding_size
				while((padding_size + size + (unsigned long) current) % 16 != 0){
					padding_size = padding_size + 1;
				}
				//Set the payload data stored in the current block header equal to the size passed to the function
				current->payload = size;

				//Initialize the size_alloc data of the current block header to account for the new padding_size, the size 
				//passed to the function, and the header size
				current->size_alloc = padding_size + size + 8;

				//Set the current block as not Free
				Set_Allocated(current);
				
				//Compute Block Size
				block_size = Get_Size(current);
				
				//Get a pointer to the next block header
				current = Get_Next_Header(current, block_size);
				
				//If the new block is not the last block
				if(!Is_Last(current)){
					//Initialize the size_alloc data in the block header to account for 
					//the payload size, the block size, and the block header size
					current->size_alloc = 8 - block_size + payload;
					//Initialize the payload data in the block header to the size of the block - the header size
					current->payload = current->size_alloc - 8;
				}	
			}
			//Return the pointer to the first address of the payload
			return retVal;
		}
		//Keep searching for available blocks
		current = Get_Next_Header(current, block_size);
	}
   	// return NULL if we didn't find a block
    return NULL;
}

// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr){
    // traverse the list and check all pointers to find the correct block 
    // if you reach the end of the list without finding it return -1
	
	//LOCAL VARIABLES
	BLOCK_HEADER* current = first_header;	
	BLOCK_HEADER* next;	
	BLOCK_HEADER* after_next;	
	int padding_size = 0;
	int find_pointer = 0;
	int find_calc = 1;		//Stores the difference between the current block in the trace and the desired block
	
	//2.1  free the block
	// 
	// While the current block is not the last block
	while(!Is_Last(current)){
		//If the current block is not allocated yet
		if(Not_Free(current)){
			//If the current pointer in the trace is equal to the one we are searching for
			find_calc = 8 + (unsigned long)current - (unsigned long)ptr;
			if(find_calc == 0){
				//Store the padding size of the block in a local variable
				padding_size  = Get_Padding(current);
				//Change the found block's payload data to include the found padding size
				current->payload += padding_size;
				//Set the current block to free
				Set_Free(current);
				//Set find_pointer to 1, indicating that the desired pointer was found
				find_pointer = 1;
			}
		}
		//Keep searching for the desired block
		current = Get_Next_Header(current, Get_Size(current));
	}

	//2.2 coalesce adjacent free blocks
	//
	//Set the current header block to the first block
	current = first_header;
	//If the desired pointer was found 
	if(find_pointer){
		//While the current block is not the last block
		while(!Is_Last(current)){
			//Initialize the local variable "next" to the next block
			next = Get_Next_Header(current, Get_Size(current));
			//Initialize the local variable "after_next" to the next block after the "next" block	
			after_next = Get_Next_Header(next, Get_Size(next));
			//If the current block in the trace is free
			if(!Not_Free(current)){
				//If the "next" block in the trace if free
				if(!Not_Free(next)){
					//While the block after the "next" block is free
					while(!Not_Free(after_next)){
						//Initialize "after_next" with a pointer to the last block which is free after the current block in the trace
						after_next = Get_Next_Header(after_next, Get_Size(after_next));
					}
					//Set the size_alloc data of the current block in the trace to the difference between the last free block and the current block
					current->size_alloc =(unsigned long)after_next-(unsigned long)current;
					//Set the payload data of the current block in the trace to the size of the current block - the size of the block header
					current->payload = current-> size_alloc - 8;
					//Keep getting the next block header until the last block header is reached
					current = Get_Next_Header(current, Get_Size(current));
					continue;
				}
			}
			//If the current block in the trace is not free, keep looking for a free block
			current = Get_Next_Header(current, Get_Size(current));
		}
	}
	//If the pointer is found, return 0
	if(find_pointer){
		return 0;
	}
	//If the pointer is not found, return -1
    return -1;
}

