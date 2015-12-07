#ifdef SUPPORT_UTF
if (utf && c > MAX_VALUE_FOR_SINGLE_CHAR)
      mclength = PRIV(ord2utf)(c, mcbuffer);
    else
#endif

     {
     mcbuffer[0] = c;
     mclength = 1;
     }
