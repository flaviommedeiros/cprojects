#ifdef COMPILE_PCRE32
if (chars[0] == NOTACHAR && chars[1] == 0)
#else
      if (chars[0] == NOTACHAR)
#endif
        {
        chars[0] = chr;
        chars[1] = mask;
        }
      else
        {
        mask |= chars[0] ^ chr;
        chr |= mask;
        chars[0] = chr;
        chars[1] |= mask;
        }
