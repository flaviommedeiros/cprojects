switch (family)
    {
#ifdef PF_INET
    case -1:
      return PF_INET;
#endif

#ifdef PF_INET6
    case -2:
      return PF_INET6;
#endif
    }
