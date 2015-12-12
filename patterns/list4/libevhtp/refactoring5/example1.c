#ifdef USE_POSIX_API_REGION_OPTION
if (IS_POSIX_REGION(msa->options)) {
	    posix_regmatch_t* rmt = (posix_regmatch_t* )region;

	    rmt[0].rm_so = sstart - str;
	    rmt[0].rm_eo = s      - str;
	    for (i = 1; i <= num_mem; i++) {
	      if (mem_end_stk[i] != INVALID_STACK_INDEX) {
		if (BIT_STATUS_AT(reg->bt_mem_start, i))
		  rmt[i].rm_so = STACK_AT(mem_start_stk[i])->u.mem.pstr - str;
		else
		  rmt[i].rm_so = (UChar* )((void* )(mem_start_stk[i])) - str;

		rmt[i].rm_eo = (BIT_STATUS_AT(reg->bt_mem_end, i)
				? STACK_AT(mem_end_stk[i])->u.mem.pstr
				: (UChar* )((void* )mem_end_stk[i])) - str;
	      }
	      else {
		rmt[i].rm_so = rmt[i].rm_eo = ONIG_REGION_NOTPOS;
	      }
	    }
	  }
	  else {
#endif /* USE_POSIX_API_REGION_OPTION */
	    region->beg[0] = sstart - str;
	    region->end[0] = s      - str;
	    for (i = 1; i <= num_mem; i++) {
	      if (mem_end_stk[i] != INVALID_STACK_INDEX) {
		if (BIT_STATUS_AT(reg->bt_mem_start, i))
		  region->beg[i] = STACK_AT(mem_start_stk[i])->u.mem.pstr - str;
		else
		  region->beg[i] = (UChar* )((void* )mem_start_stk[i]) - str;

		region->end[i] = (BIT_STATUS_AT(reg->bt_mem_end, i)
				  ? STACK_AT(mem_end_stk[i])->u.mem.pstr
				  : (UChar* )((void* )mem_end_stk[i])) - str;
	      }
	      else {
		region->beg[i] = region->end[i] = ONIG_REGION_NOTPOS;
	      }
	    }

#ifdef USE_CAPTURE_HISTORY
	    if (reg->capture_history != 0) {
              int r;
              OnigCaptureTreeNode* node;

              if (IS_NULL(region->history_root)) {
                region->history_root = node = history_node_new();
                CHECK_NULL_RETURN_MEMERR(node);
              }
              else {
                node = region->history_root;
                history_tree_clear(node);
              }

              node->group = 0;
              node->beg   = sstart - str;
              node->end   = s      - str;

              stkp = stk_base;
              r = make_capture_history_tree(region->history_root, &stkp,
                                            stk, (UChar* )str, reg);
              if (r < 0) {
                best_len = r; /* error code */
                goto finish;
              }
	    }
#endif /* USE_CAPTURE_HISTORY */
#ifdef USE_POSIX_API_REGION_OPTION
	  }
