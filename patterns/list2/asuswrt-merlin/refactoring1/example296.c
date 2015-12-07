if (daemon->log_fac != -1)
    log_fac = daemon->log_fac;
#ifdef LOG_LOCAL0
  else if (option_bool(OPT_DEBUG))
    log_fac = LOG_LOCAL0;
#endif
