#ifdef SUPPORT_UCP
if (md->use_ucp)
            {
            if (c == '_') cur_is_word = TRUE; else
              {
              int cat = UCD_CATEGORY(c);
              cur_is_word = (cat == ucp_L || cat == ucp_N);
              }
            }
          else
#endif
          cur_is_word = c < 256 && (md->ctypes[c] & ctype_word) != 0;
