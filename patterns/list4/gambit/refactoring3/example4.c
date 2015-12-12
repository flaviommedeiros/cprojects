switch (family)
    {
#ifdef PF_INET
    case PF_INET:
      return ___FIX(-1);
#endif

#ifdef PF_INET6
    case PF_INET6:
      return ___FIX(-2);
#endif
    }
