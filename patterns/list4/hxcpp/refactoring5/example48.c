#ifdef SUPPORT_UTF8
if (utf8) { GETCHARLEN(c, ptr, clen); } else
#endif  /* SUPPORT_UTF8 */
    c = *ptr;
