#ifdef RLIM_INFINITY
if (rl.rlim_max == RLIM_INFINITY)
      strcpy(strbuff, "INFINITY");
    else
#endif
      sprintf(strbuff, fmt, rl.rlim_max);
