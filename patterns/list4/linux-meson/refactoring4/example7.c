#if defined(CONFIG_ARCH_MESONG9BB)
if (!stat->cmd_busy && (!((esta >> 16) & 7)))
#else
        if (!stat->cmd_busy && (!((esta >> 11) & 7)))
#endif
        //if(!stat->cmd_busy)
            return 0;
