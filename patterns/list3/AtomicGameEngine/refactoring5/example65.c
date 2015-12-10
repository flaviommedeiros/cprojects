#ifdef SUPPORT_UCP
if (md->use_ucp)
            {
            c = eptr[-1];
            if (c == '_') prev_is_word = TRUE; else
              {
              int cat = UCD_CATEGORY(c);
              prev_is_word = (cat == ucp_L || cat == ucp_N);
              }
            }
          else
#endif
          prev_is_word = MAX_255(eptr[-1])
            && ((md->ctypes[eptr[-1]] & ctype_word) != 0);
