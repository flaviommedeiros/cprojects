if (!base
      || *systemId == T('/')
#if (defined(WIN32) || defined(__WATCOMC__))
      || *systemId == T('\\')
      || (isAsciiLetter(systemId[0]) && systemId[1] == T(':'))
#endif
     )
    return systemId;
