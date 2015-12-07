#ifdef SUPPORT_UTF
if (utf)
  {
  GETCHAR(c, ptr);
  }
else
#endif  /* SUPPORT_UTF */
  c = *ptr;
