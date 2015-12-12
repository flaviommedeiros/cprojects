#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
if (map != NULL)
#endif
          {
#if defined SUPPORT_UTF && defined COMPILE_PCRE8
          if (utf)
            {
            for (c = 0; c < 16; c++) start_bits[c] |= map[c];
            for (c = 128; c < 256; c++)
              {
              if ((map[c/8] && (1 << (c&7))) != 0)
                {
                int d = (c >> 6) | 0xc0;            /* Set bit for this starter */
                start_bits[d/8] |= (1 << (d&7));    /* and then skip on to the */
                c = (c & 0xc0) + 0x40 - 1;          /* next relevant character. */
                }
              }
            }
          else
#endif
            {
            /* In non-UTF-8 mode, the two bit maps are completely compatible. */
            for (c = 0; c < 32; c++) start_bits[c] |= map[c];
            }
          }
