#ifdef SUPPORT_UTF
if (utf)
        {
        /* Get status of previous character */

        if (eptr == md->start_subject) prev_is_word = FALSE; else
          {
          PCRE_PUCHAR lastptr = eptr - 1;
          BACKCHAR(lastptr);
          if (lastptr < md->start_used_ptr) md->start_used_ptr = lastptr;
          GETCHAR(c, lastptr);
#ifdef SUPPORT_UCP
          if (md->use_ucp)
            {
            if (c == '_') prev_is_word = TRUE; else
              {
              int cat = UCD_CATEGORY(c);
              prev_is_word = (cat == ucp_L || cat == ucp_N);
              }
            }
          else
#endif
          prev_is_word = c < 256 && (md->ctypes[c] & ctype_word) != 0;
          }

        /* Get status of next character */

        if (eptr >= md->end_subject)
          {
          SCHECK_PARTIAL();
          cur_is_word = FALSE;
          }
        else
          {
          GETCHAR(c, eptr);
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
          }
        }
      else
#endif

      /* Not in UTF-8 mode, but we may still have PCRE_UCP set, and for
      consistency with the behaviour of \w we do use it in this case. */

        {
        /* Get status of previous character */

        if (eptr == md->start_subject) prev_is_word = FALSE; else
          {
          if (eptr <= md->start_used_ptr) md->start_used_ptr = eptr - 1;
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
          }

        /* Get status of next character */

        if (eptr >= md->end_subject)
          {
          SCHECK_PARTIAL();
          cur_is_word = FALSE;
          }
        else
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
        }
