switch (info->si_code)
            {
#ifdef SI_ASYNCNL
            case SI_ASYNCNL: si_code_str = "SI_ASYNCNL"; break;
#endif
#ifdef SI_SIGIO
            case SI_SIGIO: si_code_str = "Queued SIGIO"; break;
#endif
#ifdef SI_ASYNCIO
            case SI_ASYNCIO: si_code_str = "Asynchronous I/O request completed"; break;
#endif
#ifdef SI_MESGQ
            case SI_MESGQ: si_code_str = "Message queue state changed"; break;
#endif
            case SI_TIMER: si_code_str = "Timer expiration"; break;
            case SI_QUEUE: si_code_str = "Sigqueue() signal"; break;
            case SI_USER: si_code_str = "User function (kill, sigsend, abort, etc.)"; break;
#ifdef SI_KERNEL
            case SI_KERNEL: si_code_str = "Kernel signal"; break;
#endif
/* Dragonfly defines SI_USER and SI_UNDEFINED both as zero: */
/* For some reason, the PGI compiler will not let us combine these two
   #if tests into a single statement.  Sigh. */
#if defined(SI_UNDEFINED)
#if SI_UNDEFINED != SI_USER
            case SI_UNDEFINED: si_code_str = "Undefined code"; break;
#endif
#endif
            }
