static unsigned char
internal_function __attribute ((pure))
re_string_fetch_byte_case (re_string_t *pstr)
{
  if (BE (!pstr->mbs_allocated, 1))
    return re_string_fetch_byte (pstr);

#ifdef RE_ENABLE_I18N
  if (pstr->offsets_needed)
    {
      int off, ch;

      /* For tr_TR.UTF-8 [[:islower:]] there is
	 [[: CAPITAL LETTER I WITH DOT lower:]] in mbs.  Skip
	 in that case the whole multi-byte character and return
	 the original letter.  On the other side, with
	 [[: DOTLESS SMALL LETTER I return [[:I, as doing
	 anything else would complicate things too much.  */

      if (!re_string_first_byte (pstr, pstr->cur_idx))
	return re_string_fetch_byte (pstr);

      off = pstr->offsets[pstr->cur_idx];
      ch = pstr->raw_mbs[pstr->raw_mbs_idx + off];

      if (! isascii (ch))
	return re_string_fetch_byte (pstr);

      re_string_skip_bytes (pstr,
			    re_string_char_size_at (pstr, pstr->cur_idx));
      return ch;
    }
#endif

  return pstr->raw_mbs[pstr->raw_mbs_idx + pstr->cur_idx++];
}
