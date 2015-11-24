switch (code[pos++])
      {
      case Cend:
	*can_be_null = 1;
	return;
      case Cbol:
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
      case Csyntaxspec:
	syntaxcode = code[pos++];
	for (a = 0; a < 256; a++)
	  if (SYNTAX(a) == syntaxcode)
	    fastmap[a] = 1;
	return;
      case Cnotsyntaxspec:
	syntaxcode = code[pos++];
	for (a = 0; a < 256; a++)
	  if (SYNTAX(a) != syntaxcode)
	    fastmap[a] = 1;
	return;
      case Ceol:
	fastmap['\n'] = 1;
	if (*can_be_null == 0)
	  *can_be_null = 2;  /* can match null, but only at end of buffer*/
	return;
      case Cset:
	for (a = 0; a < 256/8; a++)
	  if (code[pos + a] != 0)
	    for (b = 0; b < 8; b++)
	      if (code[pos + a] & (1 << b))
		fastmap[(a << 3) + b] = 1;
	pos += 256/8;
	return;
      case Cexact:
	fastmap[(unsigned char)code[pos]] = 1;
	return;
      case Canychar:
	for (a = 0; a < 256; a++)
	  if (a != '\n')
	    fastmap[a] = 1;
	return;
      case Cstart_memory:
      case Cend_memory:
	pos++;
	break;
      case Cmatch_memory:
	/* should this ever happen for sensible patterns??? */
	*can_be_null = 1;
	return;
      case Cjump:
      case Cdummy_failure_jump:
      case Cupdate_failure_jump:
      case Cstar_jump:
	a = (unsigned char)code[pos++];
	a |= (unsigned char)code[pos++] << 8;
	pos += (int)(short)a;
	if (visited[pos])
	  {
	    /* argh... the regexp contains empty loops.  This is not
	       good, as this may cause a failure stack overflow when
	       matching.  Oh well. */
	    /* this path leads nowhere; pursue other paths. */
	    return;
	  }
	visited[pos] = 1;
	break;
      case Cfailure_jump:
	a = (unsigned char)code[pos++];
	a |= (unsigned char)code[pos++] << 8;
	a = pos + (int)(short)a;
	re_compile_fastmap_aux(code, a, visited, can_be_null, fastmap);
	break;
      default:
	abort();  /* probably some opcode is missing from this switch */
	/*NOTREACHED*/
      }
