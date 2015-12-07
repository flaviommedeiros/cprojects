#ifdef SUPPORT_UTF
if (utf) { GETCHARLEN(c, ptr, clen); } else
#endif  /* SUPPORT_UTF */
    c = *ptr;
