#ifdef HAVE_SIGNALFD
if (SwooleG.use_signalfd)
    {
        swSignalfd_add(signo, func);
    }
    else
#endif
    {
        signals[signo].callback = func;
        signals[signo].active = 1;
        signals[signo].signo = signo;
        swSignal_set(signo, swSignal_async_handler, 1, 0);
    }
