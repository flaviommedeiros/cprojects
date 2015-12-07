#ifdef SUPPORT_UCP
if ((md->poptions & PCRE_UCP) != 0)
            {
            if (c == '_') right_word = TRUE; else
              {
              int cat = UCD_CATEGORY(c);
              right_word = (cat == ucp_L || cat == ucp_N);
              }
            }
          else
#endif
          right_word = c < 256 && (ctypes[c] & ctype_word) != 0;
