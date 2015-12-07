if (false
#ifdef EAFNOSUPPORT
      || err == EAFNOSUPPORT
#endif
#ifdef EPFNOSUPPORT
      || err == EPFNOSUPPORT
#endif
#ifdef ESOCKTNOSUPPORT          /* no, "sockt" is not a typo! */
      || err == ESOCKTNOSUPPORT
#endif
#ifdef EPROTONOSUPPORT
      || err == EPROTONOSUPPORT
#endif
#ifdef ENOPROTOOPT
      || err == ENOPROTOOPT
#endif
      /* Apparently, older versions of Linux and BSD used EINVAL
         instead of EAFNOSUPPORT and such.  */
      || err == EINVAL
      )
    return false;
