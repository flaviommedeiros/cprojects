# ifdef _LIBC
if (nrules != 0)
	      {
		uint32_t collseqval;
		const char *collseq = (const char *)
		  _NL_CURRENT(LC_COLLATE, _NL_COLLATE_COLLSEQWC);

		collseqval = collseq_table_lookup (collseq, c);

		for (; workp < p - chars_length ;)
		  {
		    uint32_t start_val, end_val;

		    /* We already compute the collation sequence value
		       of the characters (or collating symbols).  */
		    start_val = (uint32_t) *workp++; /* range_start */
		    end_val = (uint32_t) *workp++; /* range_end */

		    if (start_val <= collseqval && collseqval <= end_val)
		      goto char_set_matched;
		  }
	      }
	    else
# endif
	      {
		/* We set range_start_char at str_buf[0], range_end_char
		   at str_buf[4], and compared char at str_buf[2].  */
		str_buf[1] = 0;
		str_buf[2] = c;
		str_buf[3] = 0;
		str_buf[5] = 0;
		for (; workp < p - chars_length ;)
		  {
		    wchar_t *range_start_char, *range_end_char;

		    /* match if (range_start_char <= c <= range_end_char).  */

		    /* If range_start(or end) < 0, we assume -range_start(end)
		       is the offset of the collating symbol which is specified
		       as the character of the range start(end).  */

		    /* range_start */
		    if (*workp < 0)
		      range_start_char = charset_top - (*workp++);
		    else
		      {
			str_buf[0] = *workp++;
			range_start_char = str_buf;
		      }

		    /* range_end */
		    if (*workp < 0)
		      range_end_char = charset_top - (*workp++);
		    else
		      {
			str_buf[4] = *workp++;
			range_end_char = str_buf + 4;
		      }

# ifdef _LIBC
		    if (__wcscoll (range_start_char, str_buf+2) <= 0
			&& __wcscoll (str_buf+2, range_end_char) <= 0)
# else
		    if (wcscoll (range_start_char, str_buf+2) <= 0
			&& wcscoll (str_buf+2, range_end_char) <= 0)
# endif
		      goto char_set_matched;
		  }
	      }
