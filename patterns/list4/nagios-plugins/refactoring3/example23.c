switch (start_elem.type)
	    {
	    case SB_CHAR:
	      bitset_set (sbcset, start_elem.opr.ch);
	      break;
#ifdef RE_ENABLE_I18N
	    case MB_CHAR:
	      /* Check whether the array has enough space.  */
	      if (BE (mbchar_alloc == mbcset->nmbchars, 0))
		{
		  wchar_t *new_mbchars;
		  /* Not enough, realloc it.  */
		  /* +1 in case of mbcset->nmbchars is 0.  */
		  mbchar_alloc = 2 * mbcset->nmbchars + 1;
		  /* Use realloc since array is NULL if *alloc == 0.  */
		  new_mbchars = re_realloc (mbcset->mbchars, wchar_t,
					    mbchar_alloc);
		  if (BE (new_mbchars == NULL, 0))
		    goto parse_bracket_exp_espace;
		  mbcset->mbchars = new_mbchars;
		}
	      mbcset->mbchars[mbcset->nmbchars++] = start_elem.opr.wch;
	      break;
#endif /* RE_ENABLE_I18N */
	    case EQUIV_CLASS:
	      *err = build_equiv_class (sbcset,
#ifdef RE_ENABLE_I18N
					mbcset, &equiv_class_alloc,
#endif /* RE_ENABLE_I18N */
					start_elem.opr.name);
	      if (BE (*err != REG_NOERROR, 0))
		goto parse_bracket_exp_free_return;
	      break;
	    case COLL_SYM:
	      *err = build_collating_symbol (sbcset,
#ifdef RE_ENABLE_I18N
					     mbcset, &coll_sym_alloc,
#endif /* RE_ENABLE_I18N */
					     start_elem.opr.name);
	      if (BE (*err != REG_NOERROR, 0))
		goto parse_bracket_exp_free_return;
	      break;
	    case CHAR_CLASS:
	      *err = build_charclass (regexp->trans, sbcset,
#ifdef RE_ENABLE_I18N
				      mbcset, &char_class_alloc,
#endif /* RE_ENABLE_I18N */
				      (const char *) start_elem.opr.name,
				      syntax);
	      if (BE (*err != REG_NOERROR, 0))
	       goto parse_bracket_exp_free_return;
	      break;
	    default:
	      assert (0);
	      break;
	    }
