#ifdef MONITOR
if (ingdbmode != GDBCOOKIE)
      monitor_handle_exception (exceptionVector);
    else 
#endif
      gdb_handle_exception (exceptionVector);
