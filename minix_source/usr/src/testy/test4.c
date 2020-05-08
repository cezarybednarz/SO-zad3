#include <lib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>

int main(int argc, char** argv)
{
	printf("Try to change multiple times when parent is not waiting, but working - should change parent till init.\n");
	pid_t pid;

	pid = fork ();
	if (pid == 0)
	{
		/* This is the child process.  Execute the shell command. */
		pid_t old, oppid = getppid();
		int ret;
		while(1) {
			old = getppid();
			ret = changeparent();
			if (ret < 0) {
				break;
			}
			assert(old != getppid());
			assert(errno == 0);

			assert(getoppid(getpid()) == oppid);
			assert(errno == 0);
		}
		// parent się nie zmienia
		assert(old == getppid());
		assert(ret == -1);
		assert(errno == EPERM);
		
		assert(getoppid(getpid()) == oppid);
		printf("OK - you can press ctr+c\n");

	}
	else if (pid < 0)
		/* The fork failed.  Report failure.  */
		return -1;
	else
	{
		/* This is the parent process.  Wait for the child to complete.  */
		sleep(5);
	}

        return 0;
}
