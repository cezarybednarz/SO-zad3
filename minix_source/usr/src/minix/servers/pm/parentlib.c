#include "pm.h"
#include "proto.h"
#include "mproc.h"

int do_changeparent(void) {
	if(mp->mp_parent == INIT_PROC_NR)
		return(EACCES);

	if(mproc[mp->mp_parent]->mp_flags & WAITING)
		return(EINVAL);

	mp->mp_parent = mproc[mp->mp_parent]->mp_parent;
	return OK;
}


int do_getoppid(void) {
	pid_t pid = m_in.m1_i1;
	register struct mproc *rp;
	int found = 0;
	for (rp = &mproc[0]; rp < &mproc[NR_PROCS]; rp++) {
		if(rp->mp_pid == pid) {
			found = 1;
			break;
		}
	}

	if(!found || (rp->mp_first_parent == RS_NOT_INIT_PID))
		return(EINVAL);

	printf("pid rodzica to %d\n", pid);
	rp->mp_reply.m1_i1 = rp->mp_first_parent;

	return OK;
}
