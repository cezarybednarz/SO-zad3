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
	endpoint_t pm_ep;
	minix_rs_lookup("pm", &pm_ep);
	return(_syscall(pm_ep, PM_GETOPPID, &m));
}
