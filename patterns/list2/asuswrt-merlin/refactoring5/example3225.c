#ifdef SUPPORT_UTF
if (utf)
          {                           /* Braces are required because the */
          GETCHARLEN(d, ptr, ptr);    /* macro generates multiple statements */
          }
        else
#endif
        d = *ptr;
