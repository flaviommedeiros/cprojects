#ifdef SUPPORT_UTF
if (utf) { GETCHARLEN(d, (code + coptable[codevalue]), dlen); } else
#endif  /* SUPPORT_UTF */
      d = code[coptable[codevalue]];
