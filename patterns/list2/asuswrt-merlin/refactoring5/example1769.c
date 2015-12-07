#ifdef SUPPORT_UTF
if (utf) { GETCHARINC(next, ptr); } else
#endif
  next = *ptr++;
