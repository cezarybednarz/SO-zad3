#include "pm.h"
#include "proto.h"
#include "mproc.h"

int do_changeparent(void) {
	printf("changeparent()\n");
	return 123;
}

int do_getoppid(void) {
	printf("getoppid()\n");
	return 1234;
}
