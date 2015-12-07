#ifdef SUPPORT_UTF
if (common->utf)
      {
      GETCHARINC(c, cc);
      }
    else
#endif
      c = *cc++;
