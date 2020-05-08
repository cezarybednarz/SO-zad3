#include "pm.h"
#include "proto.h"
#include "mproc.h"

int do_changeparent(void) {
	printf("changeparent\n");
	if(mp->mp_parent == INIT_PROC_NR) {
		printf("zwracam EACCES\n");
		return(EACCES);
	}

	if(mproc[mp->mp_parent].mp_flags & WAITING) {
		printf("zwaracam EINVAL\n");
		return(EINVAL);
	}


	printf("zmieniam parenta [%d] z %d na %d\n", mp->mp_pid,  mproc[mp->mp_parent].mp_pid, mproc[mproc[mp->mp_parent].mp_parent].mp_pid);

	mp->mp_parent = mproc[mp->mp_parent].mp_parent;

	return OK;
}


int do_getoppid(void) {
	printf("getoppid\n");
	pid_t pid = m_in.m1_i1;
	register struct mproc *rp;
	int found = 0;
	for (rp = &mproc[0]; rp < &mproc[NR_PROCS]; rp++) {
		if(rp->mp_pid == pid) {
			found = 1;
			break;
		}
	}

	if(!found || (rp->mp_first_parent == RS_NOT_INIT_PID)) {
		printf("zwracam EINVAL\n");
		return(EINVAL);
	}

	printf("pid rodzica to %d  xd\n", rp->mp_first_parent);

	m_in.m1_i1 = rp->mp_first_parent;

	return(OK);
}
