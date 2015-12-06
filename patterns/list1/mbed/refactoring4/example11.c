#if IP_FORWARD
if (*sint_ptr == 1)
#else
      /* not-forwarding */
      if (*sint_ptr == 2)
#endif
      {
        set_ok = 1;
      }
