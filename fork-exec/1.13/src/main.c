#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	int i = 0;
	int pid = fork();

	if (pid < 0)
	{
		perror("Error during fork()");
		exit(1);
	}
	else if (pid != 0)
	{
		// what happens when we exchange 4 with 50?
		for (i = 0; i < 4; i++)
		{
			puts(" parent ");
		}
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			puts(" child ");
		}
	}
}
