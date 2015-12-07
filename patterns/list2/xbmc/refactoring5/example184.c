#ifdef SUPPORT_UTF8
if (utf8)
        {
        if (eptr == md->start_subject) prev_is_word = FALSE; else
          {
          USPTR lastptr = eptr - 1;
          while((*lastptr & 0xc0) == 0x80) lastptr--;
          if (lastptr < md->start_used_ptr) md->start_used_ptr = lastptr;
          GETCHAR(c, lastptr);
          prev_is_word = c < 256 && (md->ctypes[c] & ctype_word) != 0;
          }
        if (eptr >= md->end_subject)
          {
          SCHECK_PARTIAL();
          cur_is_word = FALSE;
          }
        else
          {
          GETCHAR(c, eptr);
          cur_is_word = c < 256 && (md->ctypes[c] & ctype_word) != 0;
          }
        }
      else
#endif

      /* Not in UTF-8 mode */

        {
        if (eptr == md->start_subject) prev_is_word = FALSE; else
          {
          if (eptr <= md->start_used_ptr) md->start_used_ptr = eptr - 1;
          prev_is_word = ((md->ctypes[eptr[-1]] & ctype_word) != 0);
          }
        if (eptr >= md->end_subject)
          {
          SCHECK_PARTIAL();
          cur_is_word = FALSE;
          }
        else cur_is_word = ((md->ctypes[*eptr] & ctype_word) != 0);
        }
