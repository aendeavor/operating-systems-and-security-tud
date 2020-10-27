#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

// ! THIS IS EXTREMELY DIRTY AND REALLY ACTUALLY AN ILLUSTRATION OF BAD STYLE
// ! FEEL FREE TO REFACTOR THIS AND PLAY WITH IT
// * ONE IDEA WOULD BE TO INTRODUCE AN ENUM FOR THE TYPE, etc.

void parse_input(int argc, char **argv, char *name, char *type, char *working_directory);

int main(int argc, char **argv)
{
	char name[256], type[4], working_directory[1024];
	parse_input(argc, argv, name, type, working_directory);

	DIR *directory;
	struct dirent *dir_pointer;

	if ((directory = opendir(working_directory)) != NULL)
	{
		while ((dir_pointer = readdir(directory)) != NULL)
		{
			if (!strcmp(dir_pointer->d_name, name))
			{
				printf("%s %c\n", dir_pointer->d_name, dir_pointer->d_type);
				// very ugly, an enum would be way better
				if ((!strcmp(type, "d") && dir_pointer->d_type == 6) || (!strcmp(type, "f") && dir_pointer->d_type == 8))
				{
					printf("%s\n", dir_pointer->d_name);
				}
			}
		}
	}
}

void parse_input(
		int argc,
		char **argv,
		char *name,
		char *type,
		char *working_directory)
{
	if (argc == 1)
		exit(1);

	// parse command line arguments
	int opt;
	optind = 1;
	while ((opt = getopt(argc, argv, "t:n:")) != -1)
	{
		switch (opt)
		{
		case 'n':
			strcpy(name, optarg);
			break;
		case 't':
			strcpy(type, optarg);
			break;
		default:
			continue;
		}
	}

	if (strcmp(argv[1], ".") != 0)
	{
		getcwd(working_directory, 256);
	}
	else if (strcmp(argv[1], "-n") && strcmp(argv[1], "-t"))
	{
		working_directory[0] = *argv[1];
	}
}
