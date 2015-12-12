#ifdef SUPPORT_UTF8
if (utf8) { GETCHARINC(next, ptr); } else
#endif
  next = *ptr++;
