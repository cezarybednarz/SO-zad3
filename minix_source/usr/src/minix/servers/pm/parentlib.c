#include "pm.h"
#include "proto.h"
#include "mproc.h"

int do_changeparent(void) {
	  register struct mproc *rp;
	  int i, pidarg, options, children;

	  children = 0;
	  for (rp = &mproc[0]; rp < &mproc[NR_PROCS]; rp++) {
		if ((rp->mp_flags & (IN_USE | TOLD_PARENT)) != IN_USE) continue;
		if (rp->mp_parent != who_p && rp->mp_tracer != who_p) continue;
		if (rp->mp_parent != who_p && (rp->mp_flags & ZOMBIE)) continue;

		/* The value of pidarg determines which children qualify. */
		if (pidarg  > 0 && pidarg != rp->mp_pid) continue;
		if (pidarg < -1 && -pidarg != rp->mp_procgrp) continue;

		children++;			/* this child is acceptable */

		if (rp->mp_tracer == who_p) {
			if (rp->mp_flags & TRACE_ZOMBIE) {
				/* Traced child meets the pid test and has exited. */
				tell_tracer(rp);
				check_parent(rp, TRUE /*try_cleanup*/);
				return(SUSPEND);
			}
			if (rp->mp_flags & TRACE_STOPPED) {
				/* This child meets the pid test and is being traced.
				 * Deliver a signal to the tracer, if any.
				 */
				for (i = 1; i < _NSIG; i++) {
					if (sigismember(&rp->mp_sigtrace, i)) {
						sigdelset(&rp->mp_sigtrace, i);

						mp->mp_reply.m_pm_lc_waitpid.status = W_STOPCODE(i);
						return(rp->mp_pid);
					}
				}
			}
		}

		if (rp->mp_parent == who_p) {
			if (rp->mp_flags & ZOMBIE) {
				/* This child meets the pid test and has exited. */
				tell_parent(rp); /* this child has already exited */
				if (!(rp->mp_flags & VFS_CALL))
					cleanup(rp);
				return(SUSPEND);
			}
		}
	  }

	  /* No qualifying child has exited.  Wait for one, unless none exists. */
	  if (children > 0) {
		/* At least 1 child meets the pid test exists, but has not exited. */
		if (options & WNOHANG) {
			return(0);    /* parent does not want to wait */
		}
		mp->mp_flags |= WAITING;	     /* parent wants to wait */
		mp->mp_wpid = (pid_t) pidarg;	     /* save pid for later */
		return(SUSPEND);		     /* do not reply, let it wait */
	  } else {
		/* No child even meets the pid test.  Return error immediately. */
		return(ECHILD);			     /* no - parent has no children */
	  }
}



int do_getoppid(void) {

}
