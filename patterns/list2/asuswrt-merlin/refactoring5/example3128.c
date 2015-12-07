#ifdef SAME_CODE_AS_BELOW
if (s->mode == BZ_M_RUNNING) {
		/*-- fast track the common case --*/
		while (1) {
			/*-- no input? --*/
			if (s->strm->avail_in == 0) break;
			/*-- block full? --*/
			if (s->nblock >= s->nblockMAX) break;
			/*progress_in = True;*/
			ADD_CHAR_TO_BLOCK(s, (uint32_t)(*(uint8_t*)(s->strm->next_in)));
			s->strm->next_in++;
			s->strm->avail_in--;
			/*s->strm->total_in++;*/
		}
	} else
#endif
	{
		/*-- general, uncommon case --*/
		while (1) {
			/*-- no input? --*/
			if (s->strm->avail_in == 0) break;
			/*-- block full? --*/
			if (s->nblock >= s->nblockMAX) break;
		//#	/*-- flush/finish end? --*/
		//#	if (s->avail_in_expect == 0) break;
			/*progress_in = True;*/
			ADD_CHAR_TO_BLOCK(s, *(uint8_t*)(s->strm->next_in));
			s->strm->next_in++;
			s->strm->avail_in--;
			/*s->strm->total_in++;*/
		//#	s->avail_in_expect--;
		}
	}
