#ifdef SUPPORT_UTF
if (common->utf)
    {
    GETCHAR(c, cc);
    }
  else
#endif
    c = *cc;
