#ifdef RE_ENABLE_I18N
if (pstr->mb_cur_max > 1)
	    {
	      Idx wcs_idx;
	      wint_t wc = WEOF;

	      if (pstr->is_utf8)
		{
		  const unsigned char *raw, *p, *end;

		  /* Special case UTF-8.  Multi-byte chars start with any
		     byte other than 0x80 - 0xbf.  */
		  raw = pstr->raw_mbs + pstr->raw_mbs_idx;
		  end = raw + (offset - pstr->mb_cur_max);
		  if (end < pstr->raw_mbs)
		    end = pstr->raw_mbs;
		  p = raw + offset - 1;
#ifdef _LIBC
		  /* We know the wchar_t encoding is UCS4, so for the simple
		     case, ASCII characters, skip the conversion step.  */
		  if (isascii (*p) && BE (pstr->trans == NULL, 1))
		    {
		      memset (&pstr->cur_state, '\0', sizeof (mbstate_t));
		      /* pstr->valid_len = 0; */
		      wc = (wchar_t) *p;
		    }
		  else
#endif
		    for (; p >= end; --p)
		      if ((*p & 0xc0) != 0x80)
			{
			  mbstate_t cur_state;
			  wchar_t wc2;
			  Idx mlen = raw + pstr->len - p;
			  unsigned char buf[6];
			  size_t mbclen;

			  const unsigned char *pp = p;
			  if (BE (pstr->trans != NULL, 0))
			    {
			      int i = mlen < 6 ? mlen : 6;
			      while (--i >= 0)
				buf[i] = pstr->trans[p[i]];
			      pp = buf;
			    }
			  /* XXX Don't use mbrtowc, we know which conversion
			     to use (UTF-8 -> UCS4).  */
			  memset (&cur_state, 0, sizeof (cur_state));
			  mbclen = __mbrtowc (&wc2, (const char *) pp, mlen,
					      &cur_state);
			  if (raw + offset - p <= mbclen
			      && mbclen < (size_t) -2)
			    {
			      memset (&pstr->cur_state, '\0',
				      sizeof (mbstate_t));
			      pstr->valid_len = mbclen - (raw + offset - p);
			      wc = wc2;
			    }
			  break;
			}
		}

	      if (wc == WEOF)
		pstr->valid_len = re_string_skip_chars (pstr, idx, &wc) - idx;
	      if (wc == WEOF)
		pstr->tip_context
		  = re_string_context_at (pstr, prev_valid_len - 1, eflags);
	      else
		pstr->tip_context = ((BE (pstr->word_ops_used != 0, 0)
				      && IS_WIDE_WORD_CHAR (wc))
				     ? CONTEXT_WORD
				     : ((IS_WIDE_NEWLINE (wc)
					 && pstr->newline_anchor)
					? CONTEXT_NEWLINE : 0));
	      if (BE (pstr->valid_len, 0))
		{
		  for (wcs_idx = 0; wcs_idx < pstr->valid_len; ++wcs_idx)
		    pstr->wcs[wcs_idx] = WEOF;
		  if (pstr->mbs_allocated)
		    memset (pstr->mbs, 255, pstr->valid_len);
		}
	      pstr->valid_raw_len = pstr->valid_len;
	    }
	  else
#endif /* RE_ENABLE_I18N */
	    {
	      int c = pstr->raw_mbs[pstr->raw_mbs_idx + offset - 1];
	      pstr->valid_raw_len = 0;
	      if (pstr->trans)
		c = pstr->trans[c];
	      pstr->tip_context = (bitset_contain (pstr->word_char, c)
				   ? CONTEXT_WORD
				   : ((IS_NEWLINE (c) && pstr->newline_anchor)
				      ? CONTEXT_NEWLINE : 0));
	    }
