#if EV_SELECT_IS_WINSOCKET
if ((oev ^ nev) & EV_WRITE)
    #endif
      if (nev & EV_WRITE)
        FD_SET (handle, (fd_set *)vec_wi);
      else
        FD_CLR (handle, (fd_set *)vec_wi);
