#ifdef RLIM_INFINITY
if (rl.rlim_cur == RLIM_INFINITY)
      strcpy(strbuff, "INFINITY");
    else
#endif
      sprintf(strbuff, fmt, rl.rlim_cur);
