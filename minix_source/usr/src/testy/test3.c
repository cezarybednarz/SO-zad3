#include <lib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>

int main(int argc, char** argv)
{
	printf("Try to change when parent is not waiting and is not init\n");
	pid_t pid, gpid = getppid();

	pid = fork ();
	if (pid == 0)
	{
		/* This is the child process.  Execute the shell command. */
		pid_t old = getppid();
		int ret = changeparent();

		// parent się zmienia
		assert(gpid == getppid());
		assert(ret == 0);
		assert(errno == 0);
		
		assert(getoppid(getpid()) == old);
		assert(errno == 0);
		printf("OK\n");
	}
	else if (pid < 0)
		/* The fork failed.  Report failure.  */
		return -1;
	else
	{
		/* This is the parent process.  Wait for the child to complete.  */
		sleep(3);
	}

        return 0;
}
