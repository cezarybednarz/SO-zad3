#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>

int changeparent(void)
{
	message m;
	endpoint_t pm_ep;
	minix_rs_lookup("pm", &pm_ep);
	_syscall(pm_ep, PM_CHANGE_PARENT, &m);

	return 0; // tutaj zmienic
}
