if (PJ_FD_COUNT(&ioqueue->rfdset)==0 &&
        PJ_FD_COUNT(&ioqueue->wfdset)==0 
#if defined(PJ_HAS_TCP) && PJ_HAS_TCP!=0
        && PJ_FD_COUNT(&ioqueue->xfdset)==0
#endif
	)
    {
#if PJ_IOQUEUE_HAS_SAFE_UNREG
	scan_closing_keys(ioqueue);
#endif
	pj_lock_release(ioqueue->lock);
	TRACE__((THIS_FILE, "     poll: no fd is set"));
        if (timeout)
            pj_thread_sleep(PJ_TIME_VAL_MSEC(*timeout));
        return 0;
    }
