#include "pm.h"
#include "proto.h"
#include "mproc.h"

int do_changeparent(void) {
	int gp_id = mproc[mp->mp_parent]->mp_parent; /* id of grandparent in mproc table */
	if(WAITING || gp_id == INIT_PROC_NR) {
		return EINVAL;
	}
	return OK;
}


int do_getoppid(void) {
	pid_t pid = m_in.m1_i1;


}
