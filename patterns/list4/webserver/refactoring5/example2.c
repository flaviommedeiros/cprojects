#ifdef HAVE_PTHREAD
if (srv->thread_num > 1) {
		ret = cherokee_thread_step_MULTI_THREAD (srv->main_thread, true);
	} else
#endif
	{
		ret = cherokee_thread_step_SINGLE_THREAD (srv->main_thread);
	}
