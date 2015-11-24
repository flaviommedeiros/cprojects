if ((errno == EINTR)
#ifdef EWOULDBLOCK
          || (errno == EWOULDBLOCK)
#endif
          || (errno == EAGAIN))
      {
        continue;
      }
