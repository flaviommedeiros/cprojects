#ifdef SUPPORT_UTF
if ((options & PCRE_UTF8) != 0)  /* All UTFs use the same flag bit */
    {
    if (start < end)
      {
      *uchardata++ = XCL_RANGE;
      uchardata += PRIV(ord2utf)(start, uchardata);
      uchardata += PRIV(ord2utf)(end, uchardata);
      }
    else if (start == end)
      {
      *uchardata++ = XCL_SINGLE;
      uchardata += PRIV(ord2utf)(start, uchardata);
      }
    }
  else
#endif  /* SUPPORT_UTF */

  /* Without UTF support, character values are constrained by the bit length,
  and can only be > 256 for 16-bit and 32-bit libraries. */

#ifdef COMPILE_PCRE8
    {}
