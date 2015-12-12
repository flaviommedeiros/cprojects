#ifdef HAVE_SIGQUEUE
if (ctl->use_sigval)
		rc = sigqueue(ctl->pid, ctl->numsig, ctl->sigdata);
	else
#endif
		rc = kill(ctl->pid, ctl->numsig);
