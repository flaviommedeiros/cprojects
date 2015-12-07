#ifdef SUPPORT_UTF
if (utf)
  {
  BACKCHAR(ptr);
  GETCHAR(c, ptr);
  }
else
#endif  /* SUPPORT_UTF */
  c = *ptr;
