if ((rl.rlim_cur > 0) &&
#ifdef RLIM_INFINITY
     (rl.rlim_cur != RLIM_INFINITY) &&
#endif
     (rl.rlim_cur <= num_open.rlim_cur)) {
    sprintf(strbuff2, fmt, rl.rlim_cur);
    sprintf(strbuff1, fmt, num_open.rlim_cur);
    sprintf(strbuff, "fds needed %s > system limit %s",
            strbuff1, strbuff2);
    store_errmsg(strbuff, 0);
    fprintf(stderr, "%s\n", msgbuff);
    return -4;
  }
