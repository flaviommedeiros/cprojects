#if EV_SELECT_IS_WINSOCKET
if ((oev ^ nev) & EV_READ)
    #endif
      if (nev & EV_READ)
        FD_SET (handle, (fd_set *)vec_ri);
      else
        FD_CLR (handle, (fd_set *)vec_ri);
