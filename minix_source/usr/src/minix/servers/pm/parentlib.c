#include "pm.h"
#include "proto.h"
#include "mproc.h"

int do_changeparent(void) {
	if(mp->mp_parent == INIT_PROC_NR) {
		return(EACCES);
	}

	if(mproc[mp->mp_parent].mp_flags & WAITING) {
		return(EPERM);
	}

	mp->mp_parent = mproc[mp->mp_parent].mp_parent;

	return OK;
}


int do_getoppid(void) {
	pid_t pid = m_in.m1_i1;
	register struct mproc *rp = find_proc(pid);

	if(!rp) {
		return(EINVAL);
	}

	if(rp->mp_first_parent == RS_NOT_INIT_PID) { /* rs is parent, but not yet initialized */
		mp->mp_reply.m1_i1 = mproc[RS_PROC_NR].mp_pid;
	}
	else {
		mp->mp_reply.m1_i1 = rp->mp_first_parent;
	}

	return(OK);
}
