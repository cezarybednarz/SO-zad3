#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>

pid_t getoppid(pid_t pid)
{
	message m;
	m.m1_i1 = pid;
	int ret = _syscall(PM_PROC_NR, PM_GETOPPID, &m);

	if(ret < 0)
		return(ret);

	return(m.m1_i1);
}
