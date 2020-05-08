#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>

int changeparent(void)
{
	message m;
	return _syscall(PM_PROC_NR, PM_CHANGE_PARENT, &m);
}
