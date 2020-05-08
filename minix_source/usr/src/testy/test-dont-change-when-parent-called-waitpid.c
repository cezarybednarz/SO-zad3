#include <lib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	printf("Try to change when parent is waiting\n");
	pid_t pid;

	pid = fork ();
	if (pid == 0)
	{
		/* This is the child process.  Execute the shell command. */
		sleep(3);
		pid_t old = getppid();
		int ret = changeparent();

		// parent się nie zmienia
		assert(old != getppid());
		assert(ret == 0);
		assert(errno == 0);
		
		assert(getoppid(getpid()) == old);
		printf("OK\n");

	}
	else if (pid < 0)
		/* The fork failed.  Report failure.  */
		return -1;
	else
	{
		pid = fork();
		if (pid== 0) { sleep(5); }
		else {
			int status;
			if (waitpid (pid, &status, 0) != pid)
      				return -1;
	}	
	}

        return 0;
}
