#ifdef SUPPORT_UCP
if ((options & PCRE_CASELESS) != 0)
#else
        /* In non 8 bit mode, we can get here even if we are not in UTF mode. */
        if (utf && (options & PCRE_CASELESS) != 0)
#endif
          {
          unsigned int othercase;
          if ((int)(othercase = UCD_OTHERCASE(c)) != c)
            {
            *class_uchardata++ = XCL_SINGLE;
            class_uchardata += PRIV(ord2utf)(othercase, class_uchardata);
            }
          }
