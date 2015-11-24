switch (signo)
        {
        case SIGILL:
        case SIGFPE: 
        case SIGSEGV: 
        case SIGBUS:
        {
            ret = snprintf(tmp, size, HOSTFORMAT "Failing at address: %p\n",
                           stacktrace_hostname, getpid(), info->si_addr);
            size -= ret;
            tmp += ret;
            break;
        }
        case SIGCHLD: 
        {
            ret = snprintf(tmp, size, HOSTFORMAT "Sending PID: %d, Sending UID: %d, Status: %d\n",
                           stacktrace_hostname, getpid(), 
                           info->si_pid, info->si_uid, info->si_status);
            size -= ret;
            tmp += ret;
            break;
        }
#ifdef SIGPOLL
        case SIGPOLL:
        {
#ifdef HAVE_SIGINFO_T_SI_FD
            ret = snprintf(tmp, size, HOSTFORMAT "Band event: %ld, File Descriptor : %d\n",
                           stacktrace_hostname, getpid(), (long)info->si_band, info->si_fd);
#elif HAVE_SIGINFO_T_SI_BAND
            ret = snprintf(tmp, size, HOSTFORMAT "Band event: %ld\n",
                           stacktrace_hostname, getpid(), (long)info->si_band);
#else
            ret = 0;
#endif
            size -= ret;
            tmp += ret;
            break;
        }
#endif
        }
