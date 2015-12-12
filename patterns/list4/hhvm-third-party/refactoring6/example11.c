if (
#if defined SUPPORT_UTF || !(defined COMPILE_PCRE8)
       c < 256 &&
#endif
       (md->ctypes[c] & ctype_digit) != 0
       )
      RRETURN(MATCH_NOMATCH);
