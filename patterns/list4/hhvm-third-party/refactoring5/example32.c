#ifdef SUPPORT_UTF
if (utf)
      {
      GETCHARINC(x, data); /* macro generates multiple statements */
      }
    else
#endif
      x = *data++;
