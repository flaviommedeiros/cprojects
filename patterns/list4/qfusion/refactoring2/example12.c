#if _POSIX_TIMERS > 0
if(hasmono > 0 || (hasmono == 0 &&
                       (hasmono=sysconf(_SC_MONOTONIC_CLOCK)) > 0))
#endif
        ret = clock_gettime(CLOCK_MONOTONIC, &ts);
