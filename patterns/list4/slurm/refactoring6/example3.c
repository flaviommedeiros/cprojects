if ( (job->task_flags & TASK_PARALLEL_DEBUG)
#ifdef BSD
	     && (_PTRACE(PT_TRACE_ME, 0, (caddr_t)0, 0) < 0) )
#elif defined(PT_TRACE_ME)
	     && (_PTRACE(PT_TRACE_ME, 0, NULL, 0) < 0)
