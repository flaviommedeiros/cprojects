if ((
#ifndef DBUG_OFF
       writtenbytes =
#endif
       (size_t) write(Filedes,Buffer,Count)) != Count)
  {
#ifndef DBUG_OFF
    if ((writtenbytes == 0 || writtenbytes == (size_t) -1) && errno == EINTR)
    {  
      DBUG_PRINT("error", ("my_quick_write() was interrupted and returned %d"
                           ".  This function does not retry the write!",
                           (int) writtenbytes));
    }
#endif
    my_errno=errno;
    return (size_t) -1;
  }
