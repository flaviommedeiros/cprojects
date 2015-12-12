#ifdef SUPPORT_UTF8
if (utf8) { GETCHARLEN(d, (code + coptable[codevalue]), dlen); } else
#endif  /* SUPPORT_UTF8 */
      d = code[coptable[codevalue]];
