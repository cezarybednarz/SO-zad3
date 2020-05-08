#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>

pid_t pm_hello_world(pid_t pid)
{
	message m;
	endpoint_t pm_ep;
	minix_rs_lookup("pm", &pm_ep);
	_syscall(pm_ep, PM_GETOPPID, &m);
}
