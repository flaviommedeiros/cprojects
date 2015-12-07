if (ch == '/'
#if (defined(WIN32) || defined(__WATCOMC__))
        || ch == '\\'
#endif
        )
      prog = s + 1;
