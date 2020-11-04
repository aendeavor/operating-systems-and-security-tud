#include "parse.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdlib.h>

void execute_command_line(struct command *cmd_struct, int num_pipes)
{
	// c)
	int old_fds[2];
	int new_fds[2];
	if (pipe(old_fds))
	{
		perror("pipe");
		exit(1);
	}

	for (int i = 0; i <= num_pipes; ++i)
	{
		int next_command_exists = num_pipes - i;
		if (next_command_exists)
		{
			if (pipe(new_fds))
			{
				perror("pipe");
				exit(1);
			}
		}

		// a)
		pid_t pid = fork();

		switch (pid)
		{
		case -1:
			perror("In fork():");
			break;
		case 0:
		{
			// CHILD

			// if there is a previous command
			if (i)
			{
				dup2(old_fds[0], STDIN_FILENO);
				close(old_fds[0]);
				close(old_fds[1]);
			}

			if (next_command_exists)
			{
				dup2(new_fds[1], STDOUT_FILENO);
				close(new_fds[0]);
				close(new_fds[1]);
			}

			// b)
			if (cmd_struct[i].input_redir)
			{
				int new_fds =
					open(cmd_struct[i].input_redir, O_CREAT, S_IRWXU);
				dup2(new_fds, STDIN_FILENO);
				close(new_fds);
			}

			if (cmd_struct[i].output_redir)
			{
				int new_fds = open(
					cmd_struct[i].output_redir,
					O_TRUNC | O_WRONLY | O_CREAT,
					S_IRWXU);
				dup2(new_fds, STDOUT_FILENO);
				close(new_fds);
			}

			execvp(cmd_struct[i].cmd[0], cmd_struct[i].cmd);
			exit(-1);
		}
		default:
			// PARENT

			// if there is a previous command
			if (i)
			{
				close(old_fds[0]);
				close(old_fds[1]);
			}

			if (next_command_exists)
			{
				old_fds[0] = new_fds[0];
				old_fds[1] = new_fds[1];
			}

			waitpid(pid, NULL, WUNTRACED);
		}
	}
}
