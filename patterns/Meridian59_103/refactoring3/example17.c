switch (*code++)
	{
	case Cend:
	  if (partend != part_2_end)
	    match_end = text - string1;
	  else
	    match_end = text - string2 + size1;
	  if (regs)
	    {
	      regs->start[0] = pos;
	      regs->end[0] = match_end;
	      if (!bufp->uses_registers)
		{
		  for (a = 1; a < RE_NREGS; a++)
		    {
		      regs->start[a] = -1;
		      regs->end[a] = -1;
		    }
		}
	      else
		{
		  for (a = 1; a < RE_NREGS; a++)
		    {
		      if (regend_text[a] == NULL)
			{
			  regs->start[a] = -1;
			  regs->end[a] = -1;
			  continue;
			}
		      if (regstart_partend[a] != part_2_end)
			regs->start[a] = regstart_text[a] - string1;
		      else
			regs->start[a] = regstart_text[a] - string2 + size1;
		      if (regend_partend[a] != part_2_end)
			regs->end[a] = regend_text[a] - string1;
		      else
			regs->end[a] = regend_text[a] - string2 + size1;
		    }
		}
	    }
	  if (failure_stack_start != initial_failure_stack)
	    SafeFree((char *)failure_stack_start);
	  return match_end - pos;
	case Cbol:
	  if (text == string1 || text[-1] == '\n') /* text[-1] always valid */
	    break;
	  goto fail;
	case Ceol:
	  if (text == string2 + size2 ||
	      (text == string1 + size1 ?
	       (size2 == 0 || *string2 == '\n') :
	       *text == '\n'))
	    break;
	  goto fail;
	case Cset:
	  NEXTCHAR(ch);
	  if (code[ch/8] & (1<<(ch & 7)))
	    {
	      code += 256/8;
	      break;
	    }
	  goto fail;
	case Cexact:
	  NEXTCHAR(ch);
	  if (ch != (unsigned char)*code++)
	    goto fail;
	  break;
	case Canychar:
	  NEXTCHAR(ch);
	  if (ch == '\n')
	    goto fail;
	  break;
	case Cstart_memory:
	  reg = *code++;
	  regmaybe_text[reg] = text;
	  regmaybe_partend[reg] = partend;
	  break;
	case Cend_memory:
	  reg = *code++;
	  regstart_text[reg] = regmaybe_text[reg];
	  regstart_partend[reg] = regmaybe_partend[reg];
	  regend_text[reg] = text;
	  regend_partend[reg] = partend;
	  break;
	case Cmatch_memory:
	  reg = *code++;
	  if (regend_text[reg] == NULL)
	    goto fail;  /* or should we just match nothing? */
	  regtext = regstart_text[reg];
	  regtextend = regend_text[reg];
	  if (regstart_partend[reg] == regend_partend[reg])
	    regpartend = regtextend;
	  else
	    regpartend = string1 + size1;
	  
	  for (;regtext != regtextend;)
	    {
	      NEXTCHAR(ch);
	      if (regtext == regpartend)
		regtext = string2;
	      regch = (unsigned char)*regtext++;
	      if (translate)
		regch = (unsigned char)translate[regch];
	      if (regch != ch)
		goto fail;
	    }
	  break;
	case Cstar_jump:
	  /* star is coded as:
	       1: failure_jump 2
	          ... code for operand of star
		  star_jump 1
	       2: ... code after star
	     We change the star_jump to update_failure_jump if we can determine
	     that it is safe to do so; otherwise we change it to an ordinary
	     jump.
	     plus is coded as
	          jump 2
	       1: failure_jump 3
	       2: ... code for operand of plus
	          star_jump 1
	       3: ... code after plus
	     For star_jump considerations this is processed identically
	     to star. */
	  a = (unsigned char)*code++;
	  a |= (unsigned char)*code++ << 8;
	  a = (int)(short)a;
	  {
	    char map[256], can_be_null;
	    char *p1, *p2;

	    p1 = code + a + 3; /* skip the failure_jump */
	    assert(p1[-3] == Cfailure_jump);
	    p2 = code;
	    /* p1 points inside loop, p2 points to after loop */
	    if (!re_do_compile_fastmap(bufp->buffer, bufp->used,
				       p2 - bufp->buffer, &can_be_null, map))
	      goto make_normal_jump;
	    /* If we might introduce a new update point inside the loop,
	       we can't optimize because then update_jump would update a
	       wrong failure point.  Thus we have to be quite careful here. */
	  loop_p1:
	    /* loop until we find something that consumes a character */
	    switch (*p1++)
	      {
              case Cbol:
              case Ceol:
              case Cbegbuf:
              case Cendbuf:
              case Cwordbeg:
              case Cwordend:
              case Cwordbound:
              case Cnotwordbound:
#ifdef EDH
	      case Cwordleft:
	      case Cwordright:
	      case Cnotwordleft:
	      case Cnotwordright:
#endif // EDH
                goto loop_p1;
              case Cstart_memory:
              case Cend_memory:
                p1++;
                goto loop_p1;
	      case Cexact:
		ch = (unsigned char)*p1++;
		if (map[ch])
		  goto make_normal_jump;
		break;
	      case Canychar:
		for (b = 0; b < 256; b++)
		  if (b != '\n' && map[b])
		    goto make_normal_jump;
		break;
	      case Cset:
		for (b = 0; b < 256; b++)
		  if ((p1[b >> 3] & (1 << (b & 7))) && map[b])
		    goto make_normal_jump;
		p1 += 256/8;
		break;
	      default:
		goto make_normal_jump;
	      }
	    /* now we know that we can't backtrack. */
	    while (p1 != p2 - 3)
	      {
		switch (*p1++)
		  {
		  case Cend:
		    abort();  /* we certainly shouldn't get this inside loop */
		    /*NOTREACHED*/
		  case Cbol:
		  case Ceol:
		  case Canychar:
		  case Cbegbuf:
		  case Cendbuf:
		  case Cwordbeg:
		  case Cwordend:
		  case Cwordbound:
		  case Cnotwordbound:
#ifdef EDH
		  case Cwordleft:
		  case Cwordright:
		  case Cnotwordleft:
		  case Cnotwordright:
#endif // EDH
		    break;
		  case Cset:
		    p1 += 256/8;
		    break;
		  case Cexact:
		  case Cstart_memory:
		  case Cend_memory:
		  case Cmatch_memory:
		  case Csyntaxspec:
		  case Cnotsyntaxspec:
		    p1++;
		    break;
		  case Cjump:
		  case Cstar_jump:
		  case Cfailure_jump:
		  case Cupdate_failure_jump:
		  case Cdummy_failure_jump:
		    goto make_normal_jump;
		  default:
		    printf("regexpr.c: processing star_jump: unknown op %d\n", p1[-1]);
		    break;
		  }
	      }
	    goto make_update_jump;
	  }
	make_normal_jump:
	  /* printf("changing to normal jump\n"); */
	  code -= 3;
	  *code = Cjump;
	  break;
	make_update_jump:
	  /* printf("changing to update jump\n"); */
	  code -= 2;
	  a += 3;  /* jump to after the Cfailure_jump */
	  code[-1] = Cupdate_failure_jump;
	  code[0] = a & 0xff;
	  code[1] = a >> 8;
	  /* fall to next case */
	case Cupdate_failure_jump:
	  failure_sp[-1].text = text;
	  failure_sp[-1].partend = partend;
	  /* fall to next case */
	case Cjump:
	  a = (unsigned char)*code++;
	  a |= (unsigned char)*code++ << 8;
	  code += (int)(short)a;
	  break;
	case Cdummy_failure_jump:
	case Cfailure_jump:
	  if (failure_sp == failure_stack_end)
	    {
	      struct failure_point *new_stack_start;

	      if (2 * failure_stack_size > MAX_FAILURES)
		  goto error;
	      new_stack_start = (struct failure_point *)
		SafeMalloc(2 * failure_stack_size * sizeof(*failure_stack_start));
	      if (new_stack_start == NULL)
		  goto error;
	      memcpy((char *)new_stack_start,
		     (char *)failure_stack_start,
		     failure_stack_size * sizeof(*failure_stack_start));
	      if (failure_stack_start != initial_failure_stack)
		  SafeFree((char *)failure_stack_start);
	      failure_stack_start = new_stack_start;
	      failure_sp = failure_stack_start + failure_stack_size;
	      failure_stack_size *= 2;
	      failure_stack_end = failure_stack_start + failure_stack_size;
	    }
	  a = (unsigned char)*code++;
	  a |= (unsigned char)*code++ << 8;
	  a = (int)(short)a;
	  if (code[-3] == Cdummy_failure_jump)
	    { /* this is only used in plus */
	      assert(*code == Cfailure_jump);
	      b = (unsigned char)code[1];
	      b |= (unsigned char)code[2] << 8;
	      failure_sp->code = code + (int)(short)b + 3;
	      failure_sp->text = NULL;
	      code += a;
	    }
	  else
	    {
	      failure_sp->code = code + a;
	      failure_sp->text = text;
	      failure_sp->partend = partend;
	    }
	  failure_sp++;
	  break;
	case Cbegbuf:
	  if (text == string1)
	    break;
	  goto fail;
	case Cendbuf:
	  if (size2 == 0 ? text == string1 + size1 : text == string2 + size2)
	    break;
	  goto fail;
	case Cwordbeg:
	  if (text == string2 + size2)
	    goto fail;
	  if (size2 == 0 && text == string1 + size1)
	    goto fail;
	  if (SYNTAX(text == string1 + size1 ? *string1 : *text) != Sword)
	    goto fail;
	  if (text == string1)
	    break;
	  if (SYNTAX(text[-1]) != Sword)
	    break;
	  goto fail;
	case Cwordend:
	  if (text == string1)
	    goto fail;
	  if (SYNTAX(text[-1]) != Sword)
	    goto fail;
	  if (text == string2 + size2)
	    break;
	  if (size2 == 0 && text == string1 + size1)
	    break;
	  if (SYNTAX(*text) == Sword)
	    goto fail;
	  break;
#ifdef EDH
	case Cwordleft:
	  if (text == string1)
	    goto fail;
	  if (SYNTAX(text[-1]) != Sword)
	    goto fail;
	  break;
	case Cwordright:
	  if (text == string2 + size2)
	    goto fail;
	  if (size2 == 0 && text == string1 + size1)
	    goto fail;
	  if (SYNTAX(*text) != Sword)
	    goto fail;
	  break;
	case Cnotwordleft:
	  if (text == string1)
	    break;
	  if (SYNTAX(text[-1]) != Sword)
	    break;
	  goto fail;
	case Cnotwordright:
	  if (text == string2 + size2)
	    break;
	  if (size2 == 0 && text == string1 + size1)
	    break;
	  if (SYNTAX(*text) != Sword)
	    break;
	  goto fail;
#endif // EDH
	case Cwordbound:
	  /* Note: as in gnu regexp, this also matches at the beginning
	     and end of buffer. */
	  if (text == string1 || text == string2 + size2 ||
	      (size2 == 0 && text == string1 + size1))
	    break;
	  if ((SYNTAX(text[-1]) == Sword) ^
	      (SYNTAX(text == string1 + size1 ? *string2 : *text) == Sword))
	    break;
	  goto fail;
	case Cnotwordbound:
	  /* Note: as in gnu regexp, this never matches at the beginning
	     and end of buffer. */
	  if (text == string1 || text == string2 + size2 ||
	      (size2 == 0 && text == string1 + size1))
	    goto fail;
	  if (((SYNTAX(text[-1]) == Sword) ^
		(SYNTAX(text == string1 + size1 ? *string2 : *text) == Sword)))
	    goto fail;
	  break;
	case Csyntaxspec:
	  NEXTCHAR(ch);
	  if (SYNTAX(ch) != *code++)
	    goto fail;
	  break;
	case Cnotsyntaxspec:
	  NEXTCHAR(ch);
	  if (SYNTAX(ch) != *code++)
	    break;
	  goto fail;
	default:
	  abort();
	  /*NOTREACHED*/
	}
