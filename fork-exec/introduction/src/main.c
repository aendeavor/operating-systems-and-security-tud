#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

// This is an introductory example which just calls fork() and
// shows information on whether you're in the parent or child
// process.
int main()
{
	pid_t pid = fork();

	if (pid == 0)
	{
		printf(
			"I'm the child. \nCHILD :: PID = %d\nCHILD :: PPID = %d\n\n",
			getpid(),
			getppid());

		char *argv[] = {"/bin/ls", "-l", NULL};
		char *env[] = {"PATH=/bin/", NULL};

		execve("/bin/ls", argv, env);
	}
	else if (pid > 0)
	{
		printf(
			"Parent here.\nPARENT :: PID = %d\nPARENT :: CPID = %d\n\n",
			getpid(),
			pid);

		int status;
		int cpid = waitpid(pid, &status, WUNTRACED);

		printf(
			"\nChild finished. [return value from wait() was %i, return status was %i]\n\n",
			cpid,
			WEXITSTATUS(status));
	}
	else if (pid < 0)
	{
		perror("In fork():");
	}

	exit(0);
}
