if (onig_is_code_in_cc(env->enc, from, cc)
#ifdef CASE_FOLD_IS_APPLIED_INSIDE_NEGATIVE_CCLASS
	&& !IS_NCCLASS_NOT(cc)
#endif
	) {
      for (i = 0; i < to_len; i++) {
	len = ONIGENC_CODE_TO_MBC(env->enc, to[i], buf);
	if (i == 0) {
	  snode = onig_node_new_str(buf, buf + len);
	  CHECK_NULL_RETURN_MEMERR(snode);

	  /* char-class expanded multi-char only
	     compare with string folded at match time. */
	  NSTRING_SET_AMBIG(snode);
	}
	else {
	  r = onig_node_str_cat(snode, buf, buf + len);
	  if (r < 0) {
	    onig_node_free(snode);
	    return r;
	  }
	}
      }

      *(iarg->ptail) = onig_node_new_alt(snode, NULL_NODE);
      CHECK_NULL_RETURN_MEMERR(*(iarg->ptail));
      iarg->ptail = &(NCDR((*(iarg->ptail))));
    }
