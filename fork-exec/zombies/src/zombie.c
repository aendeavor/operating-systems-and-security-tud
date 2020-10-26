#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

// This is mostly the introductory example, with the small difference that
// we're not awaiting the child, but waiting for 50 seconds. This will enable
// us to have a look at the process list.
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
			"Parent here.\nPARENT :: PID = %d\nPARENT :: CPID = %d\n\nYou will now have time to watch the process list. Go ahead!\n\n\n",
			getpid(),
			pid);

		// Just wait here so we can have a look at the process list.
		// The README explains why we need to wait, i.e. why we cannot
		// just exit the parent immediately.
		sleep(50);
	}
	else if (pid < 0)
	{
		perror("In fork():");
	}

	exit(0);
}
