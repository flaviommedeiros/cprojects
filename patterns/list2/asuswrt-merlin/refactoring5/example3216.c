#ifdef SUPPORT_UCP
if ((md->poptions & PCRE_UCP) != 0)
            {
            if (d == '_') left_word = TRUE; else
              {
              int cat = UCD_CATEGORY(d);
              left_word = (cat == ucp_L || cat == ucp_N);
              }
            }
          else
#endif
          left_word = d < 256 && (ctypes[d] & ctype_word) != 0;
