switch (op)
	{
	case Rend:
	  break;
	case Rnormal:
	normal_char:
	  opcode = Cexact;
	store_opcode_and_arg: /* opcode & ch must be set */
	  SET_LEVEL_START;
	  ALLOC(2);
	  STORE(opcode);
	  STORE(ch);
	  break;
	case Ranychar:
	  opcode = Canychar;
	store_opcode:
	  SET_LEVEL_START;
	  ALLOC(1);
	  STORE(opcode);
	  break;
	case Rquote:
	  abort();
	  /*NOTREACHED*/
	case Rbol:
	  if (!beginning_context)
	    if (regexp_context_indep_ops)
	      goto op_error;
	    else
	      goto normal_char;
	  opcode = Cbol;
	  goto store_opcode;
	case Reol:
	  if (!((pos >= size) ||
		((regexp_syntax & RE_NO_BK_VBAR) ?
		 (regex[pos] == '\174') :
		 (pos+1 < size && regex[pos] == '\134' &&
		  regex[pos+1] == '\174')) ||
		((regexp_syntax & RE_NO_BK_PARENS)?
		 (regex[pos] == ')'):
		 (pos+1 < size && regex[pos] == '\134' &&
		  regex[pos+1] == ')'))))
	    if (regexp_context_indep_ops)
	      goto op_error;
	    else
	      goto normal_char;
	  opcode = Ceol;
	  goto store_opcode;
	  /* NOTREACHED */
	  break;
	case Roptional:
	  if (beginning_context)
	    if (regexp_context_indep_ops)
	      goto op_error;
	    else
	      goto normal_char;
	  if (CURRENT_LEVEL_START == pattern_offset)
	    break; /* ignore empty patterns for ? */
	  ALLOC(3);
	  INSERT_JUMP(CURRENT_LEVEL_START, Cfailure_jump,
		      pattern_offset + 3);
	  break;
	case Rstar:
	case Rplus:
	  if (beginning_context)
	    if (regexp_context_indep_ops)
	      goto op_error;
	    else
	      goto normal_char;
	  if (CURRENT_LEVEL_START == pattern_offset)
	    break; /* ignore empty patterns for + and * */
	  ALLOC(9);
	  INSERT_JUMP(CURRENT_LEVEL_START, Cfailure_jump,
		      pattern_offset + 6);
	  INSERT_JUMP(pattern_offset, Cstar_jump, CURRENT_LEVEL_START);
	  if (op == Rplus)  /* jump over initial failure_jump */
	    INSERT_JUMP(CURRENT_LEVEL_START, Cdummy_failure_jump,
			CURRENT_LEVEL_START + 6);
	  break;
	case Ror:
	  ALLOC(6);
	  INSERT_JUMP(CURRENT_LEVEL_START, Cfailure_jump,
		      pattern_offset + 6);
	  if (num_jumps >= MAX_NESTING)
	    goto too_complex;
	  STORE(Cjump);
	  future_jumps[num_jumps++] = pattern_offset;
	  STORE(0);
	  STORE(0);
	  SET_LEVEL_START;
	  break;
	case Ropenpar:
	  SET_LEVEL_START;
	  if (next_register < RE_NREGS)
	    {
	      bufp->uses_registers = 1;
	      ALLOC(2);
	      STORE(Cstart_memory);
	      STORE(next_register);
	      open_registers[num_open_registers++] = next_register;
	      next_register++;
	    }
	  paren_depth++;
	  PUSH_LEVEL_STARTS;
	  current_level = 0;
	  SET_LEVEL_START;
	  break;
	case Rclosepar:
	  if (paren_depth <= 0)
	    goto parenthesis_error;
	  POP_LEVEL_STARTS;
	  current_level = regexp_precedences[Ropenpar];
	  paren_depth--;
	  if (paren_depth < num_open_registers)
	    {
	      bufp->uses_registers = 1;
	      ALLOC(2);
	      STORE(Cend_memory);
	      num_open_registers--;
	      STORE(open_registers[num_open_registers]);
	    }
	  break;
	case Rmemory:
	  if (ch == '0')
	    goto bad_match_register;
	  assert(ch >= '0' && ch <= '9');
	  bufp->uses_registers = 1;
	  opcode = Cmatch_memory;
	  ch -= '0';
	  goto store_opcode_and_arg;
	case Rextended_memory:
	  NEXTCHAR(ch);
	  if (ch < '0' || ch > '9')
	    goto bad_match_register;
	  NEXTCHAR(a);
	  if (a < '0' || a > '9')
	    goto bad_match_register;
	  ch = 10 * (a - '0') + ch - '0';
	  if (ch <= 0 || ch >= RE_NREGS)
	    goto bad_match_register;
	  bufp->uses_registers = 1;
	  opcode = Cmatch_memory;
	  goto store_opcode_and_arg;
	case Ropenset:
	  {
	    int complement,prev,offset,range,firstchar;
	    
	    SET_LEVEL_START;
	    ALLOC(1+256/8);
	    STORE(Cset);
	    offset = pattern_offset;
	    for (a = 0; a < 256/8; a++)
	      STORE(0);
	    NEXTCHAR(ch);
	    if (translate)
	      ch = translate[(unsigned char)ch];
	    if (ch == '\136')
	      {
		complement = 1;
		NEXTCHAR(ch);
		if (translate)
		  ch = translate[(unsigned char)ch];
	      }
	    else
	      complement = 0;
	    prev = -1;
	    range = 0;
	    firstchar = 1;
	    while (ch != '\135' || firstchar)
	      {
		firstchar = 0;
		if (regexp_ansi_sequences && ch == '\134')
		  {
		    NEXTCHAR(ch);
		    ANSI_TRANSLATE(ch);
		  }
		if (range)
		  {
		    for (a = prev; a <= (int)ch; a++)
		      SETBIT(pattern, offset, a);
		    prev = -1;
		    range = 0;
		  }
		else
		  if (prev != -1 && ch == '-')
		    range = 1;
		  else
		    {
		      SETBIT(pattern, offset, ch);
		      prev = ch;
		    }
		NEXTCHAR(ch);
		if (translate)
		  ch = translate[(unsigned char)ch];
	      }
	    if (range)
	      SETBIT(pattern, offset, '-');
	    if (complement)
	      {
		for (a = 0; a < 256/8; a++)
		  pattern[offset+a] ^= 0xff;
	      }
	    break;
	  }
	case Rbegbuf:
	  opcode = Cbegbuf;
	  goto store_opcode;
	case Rendbuf:
	  opcode = Cendbuf;
	  goto store_opcode;
	case Rwordchar:
	  opcode = Csyntaxspec;
	  ch = Sword;
	  goto store_opcode_and_arg;
	case Rnotwordchar:
	  opcode = Cnotsyntaxspec;
	  ch = Sword;
	  goto store_opcode_and_arg;
	case Rwordbeg:
	  opcode = Cwordbeg;
	  goto store_opcode;
	case Rwordend:
	  opcode = Cwordend;
	  goto store_opcode;
	case Rwordbound:
	  opcode = Cwordbound;
	  goto store_opcode;
	case Rnotwordbound:
	  opcode = Cnotwordbound;
	  goto store_opcode;
#ifdef EDH
	case Rwordleft:
	  opcode = Cwordleft;
	  goto store_opcode;
	case Rwordright:
	  opcode = Cwordright;
	  goto store_opcode;
	case Rnotwordleft:
	  opcode = Cnotwordleft;
	  goto store_opcode;
	case Rnotwordright:
	  opcode = Cnotwordright;
	  goto store_opcode;
#endif // EDH
	default:
	  abort();
	}
