#include "simplefs-ops.h"
extern struct filehandle_t file_handle_array[MAX_OPEN_FILES]; // Array for storing opened files

// void initializeArray()
// {
// 	for(int i=0;i<MAX_OPEN_FILES;i++)
// 	{
// 		file_handle_array[i].inode_number=-1;
// 		file_handle_array[i].offset=-1;
// 	}
// }

int simplefs_create(char *filename){
    /*
	    Create file with name `filename` from disk
	*/
	struct inode_t bruh;
	for(int i=0;i<NUM_INODES;i++)
	{
		
		simplefs_readInode(i, &bruh);
		if(bruh.status==INODE_FREE)
			continue;
		if(strcmp(filename,bruh.name)==0)
		{
			return -1;
		}
	}
	int a =  simplefs_allocInode();
	if(a==-1)
		return -1;
	struct inode_t myinode;
	memcpy(myinode.name,filename,MAX_NAME_STRLEN);
	myinode.status=INODE_IN_USE;
	myinode.file_size=0;
	simplefs_writeInode(a, &myinode);
	


    return -1;
}


void simplefs_delete(char *filename){
    /*
	    delete file with name `filename` from disk
		

	*/
	struct inode_t bruh;
	for(int i=0;i<NUM_INODES;i++)
	{
		
		simplefs_readInode(i, &bruh);
		if(bruh.status==INODE_FREE)
			continue;
		if(strcmp(filename,bruh.name)==0)
		{
			for(int j=0;j<MAX_FILE_SIZE;j++)
			{
				if(bruh.direct_blocks[i] != -1)
					simplefs_freeDataBlock(bruh.direct_blocks[i]);

			}
			simplefs_freeInode(i);
			break;
		}
	}
	return;
}

int simplefs_open(char *filename){
    /*
	    open file with name `filename`
	*/
	struct inode_t bruh;
	for(int i=0;i<NUM_INODES;i++)
	{
		
		simplefs_readInode(i, &bruh);
		if(bruh.status==INODE_FREE)
			continue;
		if(strcmp(filename,bruh.name)==0)
		{
			for(int j=0;j<MAX_OPEN_FILES;j++)
			{
				if(file_handle_array[j].inode_number == -1)
				{
					file_handle_array[j].inode_number=i;
					file_handle_array[j].offset=0;
					return j;
				}
				
			}
			return -1;
			break;
		}
	}
    return -1;
}

void simplefs_close(int file_handle){
    /*
	    close file pointed by `file_handle`
	*/
	file_handle_array[file_handle].inode_number=-1;
	file_handle_array[file_handle].offset=0;

}

int simplefs_read(int file_handle, char *buf, int nbytes){
    /*
	    read `nbytes` of data into `buf` from file pointed by `file_handle` starting at current offset
	*/
    return -1;
}


int simplefs_write(int file_handle, char *buf, int nbytes){
    /*
	    write `nbytes` of data from `buf` to file pointed by `file_handle` starting at current offset
	*/
	int c=0;
	struct inode_t bruh;
	int myoffset = file_handle_array[file_handle].offset;
	int myindex = file_handle_array[file_handle].inode_number;
	int curr_block=myoffset/BLOCKSIZE;
	int off_on_block=myoffset%BLOCKSIZE;
	int blocks_needed;
	if(nbytes==0)
		blocks_needed=0;
	if(off_on_block+nbytes<=BLOCKSIZE)
	{
		if(off_on_block==0)
		blocks_needed=1;
		else
		blocks_needed=0;
	}
	else {
		if(off_on_block==0)
		{
			if(nbytes%BLOCKSIZE==0)
				blocks_needed=nbytes/BLOCKSIZE;
			else blocks_needed=nbytes/BLOCKSIZE+1;


		}
		else {
			int new=nbytes-(BLOCKSIZE-off_on_block);
			if(new%BLOCKSIZE==0)
				blocks_needed=nbytes/BLOCKSIZE;
			else blocks_needed=nbytes/BLOCKSIZE+1;
		}
	}
	simplefs_readInode(myindex, &bruh);
	int max_inc=0;
	for(int i=0;i<MAX_FILE_SIZE;i++)
	{
		if(bruh.direct_blocks[i]==-1)
			max_inc++;
	}
	if(blocks_needed>max_inc)
		return -1;
	for(int i=0;i<blocks_needed;i++)
	{
		int z=simplefs_allocDataBlock();
		if(z==-1)
			return -1;
		for(int j=0;j<MAX_FILE_SIZE;j++)
		{
			if(bruh.direct_blocks[j]==-1)
				bruh.direct_blocks[j]=z;
		}

	}
	int copy=nbytes;
	while(copy>0)
	{
		char temp[BLOCKSIZE];
		read
	}
    return -1;
}


int simplefs_seek(int file_handle, int nseek){
    /*
	   increase `file_handle` offset by `nseek`
	*/
    return -1;
}