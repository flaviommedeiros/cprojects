#ifdef RE_ENABLE_I18N
if (dfa->mb_cur_max > 1)
		for (j = 0; j < BITSET_WORDS; ++j)
		  any_set |= (accepts[j] &= (dfa->word_char[j] | ~dfa->sb_char[j]));
	      else
#endif
		for (j = 0; j < BITSET_WORDS; ++j)
		  any_set |= (accepts[j] &= dfa->word_char[j]);
