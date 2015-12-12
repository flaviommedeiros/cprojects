switch (optid) {
#ifndef DBUG_OFF
  case '#':
    if (!opt_debug)
      opt_debug= "d:t";
    DBUG_SET_INITIAL(argument ? argument : opt_debug);
    opt_ndb_endinfo= 1;
    break;
#endif
  case 'V':
    ndb_std_print_version();
    exit(0);
  case '?':
    (*g_ndb_opt_usage)();
    exit(0);
  }
