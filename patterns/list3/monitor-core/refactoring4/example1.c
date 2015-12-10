#ifdef TDF_NOLOAD
if ((kp->ki_tdflags & TDF_NOLOAD) != 0)
#else
      if ((kp->ki_flag & P_NOLOAD) != 0)
#endif
         continue;
