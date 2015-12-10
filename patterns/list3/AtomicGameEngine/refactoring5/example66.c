#ifdef SUPPORT_UCP
if (md->use_ucp)
          {
          c = *eptr;
          if (c == '_') cur_is_word = TRUE; else
            {
            int cat = UCD_CATEGORY(c);
            cur_is_word = (cat == ucp_L || cat == ucp_N);
            }
          }
        else
#endif
        cur_is_word = MAX_255(*eptr)
          && ((md->ctypes[*eptr] & ctype_word) != 0);
