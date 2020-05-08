#include <lib.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>

int main(int argc, char** argv)
{
	printf("Try to change when oparent is dead, so init is actual parent\n\nIMPORTANT: remember to change code, when grtoppid never returns 0\n");
	pid_t oppid = getpid(), pid;

	pid = fork ();
	if (pid == 0)
	{
		sleep(1);
		pid_t old = getppid();
		int ret = changeparent();
		assert(old == 1);
		assert(old == getppid());
		assert(errno == EACCES);
		
		errno=0;
		
		/* simplier version */
		// assert(oppid == getoppid(getpid()));
		// assert(errno == 0); 

		/* normal version */
		assert(getoppid(getpid()) == 0);
		assert(errno == 0);


		printf("OK\n");
	}
	else if (pid < 0)
		return -1;
	else
	{
	}

        return 0;
}
