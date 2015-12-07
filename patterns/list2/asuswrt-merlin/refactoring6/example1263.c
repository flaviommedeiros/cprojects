if (err == ECONNREFUSED
#ifdef ENETUNREACH
        || err == ENETUNREACH   /* network is unreachable */
#endif
#ifdef EHOSTUNREACH
        || err == EHOSTUNREACH  /* host is unreachable */
#endif
        )
      return false;
