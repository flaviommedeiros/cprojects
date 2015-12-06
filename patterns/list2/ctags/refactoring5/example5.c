#ifdef RE_ENABLE_I18N
if (dfa->mb_cur_max > 1)
	    bitset_merge (accepts, dfa->sb_char);
	  else
#endif
	    bitset_set_all (accepts);
