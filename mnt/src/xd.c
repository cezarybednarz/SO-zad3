// PLIK DO USUNIĘCIA, SŁUŻY TYLKO DO TESTOWANIA

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <minix/rs.h>
#include <sys/cdefs.h>

#include <minix/com.h>
#include <minix/config.h>
#include <minix/ipc.h>
#include <minix/endpoint.h>
#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/const.h>
#include <minix/type.h>
#include <minix/ds.h>
#include <minix/rs.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <lib.h>

void fun1() {
	message m;
	endpoint_t pm_ep;
	minix_rs_lookup("pm", &pm_ep);
	_syscall(pm_ep, PM_CHANGE_PARENT, &m);
}

void fun2() {
	message m;
	endpoint_t pm_ep;
	minix_rs_lookup("pm", &pm_ep);
	_syscall(pm_ep, PM_GETOPPID, &m);
}

int main() {
	fun1();
	fun2();
}
