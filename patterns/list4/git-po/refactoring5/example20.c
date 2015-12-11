#ifdef RE_ENABLE_I18N
if (input->mb_cur_max > 1)
	{
	  wint_t wc = re_string_wchar_at (input,
					  re_string_cur_idx (input) + 1);
	  token->word_char = IS_WIDE_WORD_CHAR (wc) != 0;
	}
      else
#endif
	token->word_char = IS_WORD_CHAR (c2) != 0;
