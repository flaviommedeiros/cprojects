switch(type)
  {
  case OP_SOD:
  OP1(SLJIT_MOV, TMP1, 0, ARGUMENTS, 0);
  OP1(SLJIT_MOV, TMP1, 0, SLJIT_MEM1(TMP1), SLJIT_OFFSETOF(jit_arguments, begin));
  add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, STR_PTR, 0, TMP1, 0));
  return cc;

  case OP_SOM:
  OP1(SLJIT_MOV, TMP1, 0, ARGUMENTS, 0);
  OP1(SLJIT_MOV, TMP1, 0, SLJIT_MEM1(TMP1), SLJIT_OFFSETOF(jit_arguments, str));
  add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, STR_PTR, 0, TMP1, 0));
  return cc;

  case OP_NOT_WORD_BOUNDARY:
  case OP_WORD_BOUNDARY:
  add_jump(compiler, &common->wordboundary, JUMP(SLJIT_FAST_CALL));
  add_jump(compiler, backtracks, JUMP(type == OP_NOT_WORD_BOUNDARY ? SLJIT_C_NOT_ZERO : SLJIT_C_ZERO));
  return cc;

  case OP_NOT_DIGIT:
  case OP_DIGIT:
  /* Digits are usually 0-9, so it is worth to optimize them. */
  detect_partial_match(common, backtracks);
#if defined SUPPORT_UTF && defined COMPILE_PCRE8
  if (common->utf && is_char7_bitset((const pcre_uint8*)common->ctypes - cbit_length + cbit_digit, FALSE))
    read_char7_type(common, type == OP_NOT_DIGIT);
  else
#endif
    read_char8_type(common, type == OP_NOT_DIGIT);
    /* Flip the starting bit in the negative case. */
  OP2(SLJIT_AND | SLJIT_SET_E, SLJIT_UNUSED, 0, TMP1, 0, SLJIT_IMM, ctype_digit);
  add_jump(compiler, backtracks, JUMP(type == OP_DIGIT ? SLJIT_C_ZERO : SLJIT_C_NOT_ZERO));
  return cc;

  case OP_NOT_WHITESPACE:
  case OP_WHITESPACE:
  detect_partial_match(common, backtracks);
#if defined SUPPORT_UTF && defined COMPILE_PCRE8
  if (common->utf && is_char7_bitset((const pcre_uint8*)common->ctypes - cbit_length + cbit_space, FALSE))
    read_char7_type(common, type == OP_NOT_WHITESPACE);
  else
#endif
    read_char8_type(common, type == OP_NOT_WHITESPACE);
  OP2(SLJIT_AND | SLJIT_SET_E, SLJIT_UNUSED, 0, TMP1, 0, SLJIT_IMM, ctype_space);
  add_jump(compiler, backtracks, JUMP(type == OP_WHITESPACE ? SLJIT_C_ZERO : SLJIT_C_NOT_ZERO));
  return cc;

  case OP_NOT_WORDCHAR:
  case OP_WORDCHAR:
  detect_partial_match(common, backtracks);
#if defined SUPPORT_UTF && defined COMPILE_PCRE8
  if (common->utf && is_char7_bitset((const pcre_uint8*)common->ctypes - cbit_length + cbit_word, FALSE))
    read_char7_type(common, type == OP_NOT_WORDCHAR);
  else
#endif
    read_char8_type(common, type == OP_NOT_WORDCHAR);
  OP2(SLJIT_AND | SLJIT_SET_E, SLJIT_UNUSED, 0, TMP1, 0, SLJIT_IMM, ctype_word);
  add_jump(compiler, backtracks, JUMP(type == OP_WORDCHAR ? SLJIT_C_ZERO : SLJIT_C_NOT_ZERO));
  return cc;

  case OP_ANY:
  detect_partial_match(common, backtracks);
  read_char_range(common, common->nlmin, common->nlmax, TRUE);
  if (common->nltype == NLTYPE_FIXED && common->newline > 255)
    {
    jump[0] = CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, (common->newline >> 8) & 0xff);
    end_list = NULL;
    if (common->mode != JIT_PARTIAL_HARD_COMPILE)
      add_jump(compiler, &end_list, CMP(SLJIT_C_GREATER_EQUAL, STR_PTR, 0, STR_END, 0));
    else
      check_str_end(common, &end_list);

    OP1(MOV_UCHAR, TMP1, 0, SLJIT_MEM1(STR_PTR), 0);
    add_jump(compiler, backtracks, CMP(SLJIT_C_EQUAL, TMP1, 0, SLJIT_IMM, common->newline & 0xff));
    set_jumps(end_list, LABEL());
    JUMPHERE(jump[0]);
    }
  else
    check_newlinechar(common, common->nltype, backtracks, TRUE);
  return cc;

  case OP_ALLANY:
  detect_partial_match(common, backtracks);
#ifdef SUPPORT_UTF
  if (common->utf)
    {
    OP1(MOV_UCHAR, TMP1, 0, SLJIT_MEM1(STR_PTR), 0);
    OP2(SLJIT_ADD, STR_PTR, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(1));
#if defined COMPILE_PCRE8 || defined COMPILE_PCRE16
#if defined COMPILE_PCRE8
    jump[0] = CMP(SLJIT_C_LESS, TMP1, 0, SLJIT_IMM, 0xc0);
    OP1(SLJIT_MOV_UB, TMP1, 0, SLJIT_MEM1(TMP1), (sljit_sw)PRIV(utf8_table4) - 0xc0);
    OP2(SLJIT_ADD, STR_PTR, 0, STR_PTR, 0, TMP1, 0);
#elif defined COMPILE_PCRE16
    jump[0] = CMP(SLJIT_C_LESS, TMP1, 0, SLJIT_IMM, 0xd800);
    OP2(SLJIT_AND, TMP1, 0, TMP1, 0, SLJIT_IMM, 0xfc00);
    OP2(SLJIT_SUB | SLJIT_SET_E, SLJIT_UNUSED, 0, TMP1, 0, SLJIT_IMM, 0xd800);
    OP_FLAGS(SLJIT_MOV, TMP1, 0, SLJIT_UNUSED, 0, SLJIT_C_EQUAL);
    OP2(SLJIT_SHL, TMP1, 0, TMP1, 0, SLJIT_IMM, 1);
    OP2(SLJIT_ADD, STR_PTR, 0, STR_PTR, 0, TMP1, 0);
#endif
    JUMPHERE(jump[0]);
#endif /* COMPILE_PCRE[8|16] */
    return cc;
    }
#endif
  OP2(SLJIT_ADD, STR_PTR, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(1));
  return cc;

  case OP_ANYBYTE:
  detect_partial_match(common, backtracks);
  OP2(SLJIT_ADD, STR_PTR, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(1));
  return cc;

#ifdef SUPPORT_UTF
#ifdef SUPPORT_UCP
  case OP_NOTPROP:
  case OP_PROP:
  propdata[0] = XCL_HASPROP;
  propdata[1] = type == OP_NOTPROP ? XCL_NOTPROP : XCL_PROP;
  propdata[2] = cc[0];
  propdata[3] = cc[1];
  propdata[4] = XCL_END;
  compile_xclass_matchingpath(common, propdata, backtracks);
  return cc + 2;
#endif
#endif

  case OP_ANYNL:
  detect_partial_match(common, backtracks);
  read_char_range(common, common->bsr_nlmin, common->bsr_nlmax, FALSE);
  jump[0] = CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, CHAR_CR);
  /* We don't need to handle soft partial matching case. */
  end_list = NULL;
  if (common->mode != JIT_PARTIAL_HARD_COMPILE)
    add_jump(compiler, &end_list, CMP(SLJIT_C_GREATER_EQUAL, STR_PTR, 0, STR_END, 0));
  else
    check_str_end(common, &end_list);
  OP1(MOV_UCHAR, TMP1, 0, SLJIT_MEM1(STR_PTR), 0);
  jump[1] = CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, CHAR_NL);
  OP2(SLJIT_ADD, STR_PTR, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(1));
  jump[2] = JUMP(SLJIT_JUMP);
  JUMPHERE(jump[0]);
  check_newlinechar(common, common->bsr_nltype, backtracks, FALSE);
  set_jumps(end_list, LABEL());
  JUMPHERE(jump[1]);
  JUMPHERE(jump[2]);
  return cc;

  case OP_NOT_HSPACE:
  case OP_HSPACE:
  detect_partial_match(common, backtracks);
  read_char_range(common, 0x9, 0x3000, type == OP_NOT_HSPACE);
  add_jump(compiler, &common->hspace, JUMP(SLJIT_FAST_CALL));
  add_jump(compiler, backtracks, JUMP(type == OP_NOT_HSPACE ? SLJIT_C_NOT_ZERO : SLJIT_C_ZERO));
  return cc;

  case OP_NOT_VSPACE:
  case OP_VSPACE:
  detect_partial_match(common, backtracks);
  read_char_range(common, 0xa, 0x2029, type == OP_NOT_VSPACE);
  add_jump(compiler, &common->vspace, JUMP(SLJIT_FAST_CALL));
  add_jump(compiler, backtracks, JUMP(type == OP_NOT_VSPACE ? SLJIT_C_NOT_ZERO : SLJIT_C_ZERO));
  return cc;

#ifdef SUPPORT_UCP
  case OP_EXTUNI:
  detect_partial_match(common, backtracks);
  read_char(common);
  add_jump(compiler, &common->getucd, JUMP(SLJIT_FAST_CALL));
  OP1(SLJIT_MOV, TMP1, 0, SLJIT_IMM, (sljit_sw)PRIV(ucd_records) + SLJIT_OFFSETOF(ucd_record, gbprop));
  /* Optimize register allocation: use a real register. */
  OP1(SLJIT_MOV, SLJIT_MEM1(SLJIT_LOCALS_REG), LOCALS0, STACK_TOP, 0);
  OP1(SLJIT_MOV_UB, STACK_TOP, 0, SLJIT_MEM2(TMP1, TMP2), 3);

  label = LABEL();
  jump[0] = CMP(SLJIT_C_GREATER_EQUAL, STR_PTR, 0, STR_END, 0);
  OP1(SLJIT_MOV, TMP3, 0, STR_PTR, 0);
  read_char(common);
  add_jump(compiler, &common->getucd, JUMP(SLJIT_FAST_CALL));
  OP1(SLJIT_MOV, TMP1, 0, SLJIT_IMM, (sljit_sw)PRIV(ucd_records) + SLJIT_OFFSETOF(ucd_record, gbprop));
  OP1(SLJIT_MOV_UB, TMP2, 0, SLJIT_MEM2(TMP1, TMP2), 3);

  OP2(SLJIT_SHL, STACK_TOP, 0, STACK_TOP, 0, SLJIT_IMM, 2);
  OP1(SLJIT_MOV_UI, TMP1, 0, SLJIT_MEM1(STACK_TOP), (sljit_sw)PRIV(ucp_gbtable));
  OP1(SLJIT_MOV, STACK_TOP, 0, TMP2, 0);
  OP2(SLJIT_SHL, TMP2, 0, SLJIT_IMM, 1, TMP2, 0);
  OP2(SLJIT_AND | SLJIT_SET_E, SLJIT_UNUSED, 0, TMP1, 0, TMP2, 0);
  JUMPTO(SLJIT_C_NOT_ZERO, label);

  OP1(SLJIT_MOV, STR_PTR, 0, TMP3, 0);
  JUMPHERE(jump[0]);
  OP1(SLJIT_MOV, STACK_TOP, 0, SLJIT_MEM1(SLJIT_LOCALS_REG), LOCALS0);

  if (common->mode == JIT_PARTIAL_HARD_COMPILE)
    {
    jump[0] = CMP(SLJIT_C_LESS, STR_PTR, 0, STR_END, 0);
    /* Since we successfully read a char above, partial matching must occure. */
    check_partial(common, TRUE);
    JUMPHERE(jump[0]);
    }
  return cc;
#endif

  case OP_EODN:
  /* Requires rather complex checks. */
  jump[0] = CMP(SLJIT_C_GREATER_EQUAL, STR_PTR, 0, STR_END, 0);
  if (common->nltype == NLTYPE_FIXED && common->newline > 255)
    {
    OP2(SLJIT_ADD, TMP2, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(2));
    OP1(MOV_UCHAR, TMP1, 0, SLJIT_MEM1(STR_PTR), IN_UCHARS(0));
    if (common->mode == JIT_COMPILE)
      add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP2, 0, STR_END, 0));
    else
      {
      jump[1] = CMP(SLJIT_C_EQUAL, TMP2, 0, STR_END, 0);
      OP2(SLJIT_SUB | SLJIT_SET_U, SLJIT_UNUSED, 0, TMP2, 0, STR_END, 0);
      OP_FLAGS(SLJIT_MOV, TMP2, 0, SLJIT_UNUSED, 0, SLJIT_C_LESS);
      OP2(SLJIT_SUB | SLJIT_SET_E, SLJIT_UNUSED, 0, TMP1, 0, SLJIT_IMM, (common->newline >> 8) & 0xff);
      OP_FLAGS(SLJIT_OR | SLJIT_SET_E, TMP2, 0, TMP2, 0, SLJIT_C_NOT_EQUAL);
      add_jump(compiler, backtracks, JUMP(SLJIT_C_NOT_EQUAL));
      check_partial(common, TRUE);
      add_jump(compiler, backtracks, JUMP(SLJIT_JUMP));
      JUMPHERE(jump[1]);
      }
    OP1(MOV_UCHAR, TMP2, 0, SLJIT_MEM1(STR_PTR), IN_UCHARS(1));
    add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, (common->newline >> 8) & 0xff));
    add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP2, 0, SLJIT_IMM, common->newline & 0xff));
    }
  else if (common->nltype == NLTYPE_FIXED)
    {
    OP2(SLJIT_ADD, TMP2, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(1));
    OP1(MOV_UCHAR, TMP1, 0, SLJIT_MEM1(STR_PTR), IN_UCHARS(0));
    add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP2, 0, STR_END, 0));
    add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, common->newline));
    }
  else
    {
    OP1(MOV_UCHAR, TMP1, 0, SLJIT_MEM1(STR_PTR), IN_UCHARS(0));
    jump[1] = CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, CHAR_CR);
    OP2(SLJIT_ADD, TMP2, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(2));
    OP2(SLJIT_SUB | SLJIT_SET_U, SLJIT_UNUSED, 0, TMP2, 0, STR_END, 0);
    jump[2] = JUMP(SLJIT_C_GREATER);
    add_jump(compiler, backtracks, JUMP(SLJIT_C_LESS));
    /* Equal. */
    OP1(MOV_UCHAR, TMP1, 0, SLJIT_MEM1(STR_PTR), IN_UCHARS(1));
    jump[3] = CMP(SLJIT_C_EQUAL, TMP1, 0, SLJIT_IMM, CHAR_NL);
    add_jump(compiler, backtracks, JUMP(SLJIT_JUMP));

    JUMPHERE(jump[1]);
    if (common->nltype == NLTYPE_ANYCRLF)
      {
      OP2(SLJIT_ADD, TMP2, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(1));
      add_jump(compiler, backtracks, CMP(SLJIT_C_LESS, TMP2, 0, STR_END, 0));
      add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, CHAR_NL));
      }
    else
      {
      OP1(SLJIT_MOV, SLJIT_MEM1(SLJIT_LOCALS_REG), LOCALS1, STR_PTR, 0);
      read_char_range(common, common->nlmin, common->nlmax, TRUE);
      add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, STR_PTR, 0, STR_END, 0));
      add_jump(compiler, &common->anynewline, JUMP(SLJIT_FAST_CALL));
      add_jump(compiler, backtracks, JUMP(SLJIT_C_ZERO));
      OP1(SLJIT_MOV, STR_PTR, 0, SLJIT_MEM1(SLJIT_LOCALS_REG), LOCALS1);
      }
    JUMPHERE(jump[2]);
    JUMPHERE(jump[3]);
    }
  JUMPHERE(jump[0]);
  check_partial(common, FALSE);
  return cc;

  case OP_EOD:
  add_jump(compiler, backtracks, CMP(SLJIT_C_LESS, STR_PTR, 0, STR_END, 0));
  check_partial(common, FALSE);
  return cc;

  case OP_CIRC:
  OP1(SLJIT_MOV, TMP2, 0, ARGUMENTS, 0);
  OP1(SLJIT_MOV, TMP1, 0, SLJIT_MEM1(TMP2), SLJIT_OFFSETOF(jit_arguments, begin));
  add_jump(compiler, backtracks, CMP(SLJIT_C_GREATER, STR_PTR, 0, TMP1, 0));
  OP1(SLJIT_MOV_UB, TMP2, 0, SLJIT_MEM1(TMP2), SLJIT_OFFSETOF(jit_arguments, notbol));
  add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP2, 0, SLJIT_IMM, 0));
  return cc;

  case OP_CIRCM:
  OP1(SLJIT_MOV, TMP2, 0, ARGUMENTS, 0);
  OP1(SLJIT_MOV, TMP1, 0, SLJIT_MEM1(TMP2), SLJIT_OFFSETOF(jit_arguments, begin));
  jump[1] = CMP(SLJIT_C_GREATER, STR_PTR, 0, TMP1, 0);
  OP1(SLJIT_MOV_UB, TMP2, 0, SLJIT_MEM1(TMP2), SLJIT_OFFSETOF(jit_arguments, notbol));
  add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP2, 0, SLJIT_IMM, 0));
  jump[0] = JUMP(SLJIT_JUMP);
  JUMPHERE(jump[1]);

  add_jump(compiler, backtracks, CMP(SLJIT_C_GREATER_EQUAL, STR_PTR, 0, STR_END, 0));
  if (common->nltype == NLTYPE_FIXED && common->newline > 255)
    {
    OP2(SLJIT_SUB, TMP2, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(2));
    add_jump(compiler, backtracks, CMP(SLJIT_C_LESS, TMP2, 0, TMP1, 0));
    OP1(MOV_UCHAR, TMP1, 0, SLJIT_MEM1(STR_PTR), IN_UCHARS(-2));
    OP1(MOV_UCHAR, TMP2, 0, SLJIT_MEM1(STR_PTR), IN_UCHARS(-1));
    add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, (common->newline >> 8) & 0xff));
    add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP2, 0, SLJIT_IMM, common->newline & 0xff));
    }
  else
    {
    skip_char_back(common);
    read_char_range(common, common->nlmin, common->nlmax, TRUE);
    check_newlinechar(common, common->nltype, backtracks, FALSE);
    }
  JUMPHERE(jump[0]);
  return cc;

  case OP_DOLL:
  OP1(SLJIT_MOV, TMP2, 0, ARGUMENTS, 0);
  OP1(SLJIT_MOV_UB, TMP2, 0, SLJIT_MEM1(TMP2), SLJIT_OFFSETOF(jit_arguments, noteol));
  add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP2, 0, SLJIT_IMM, 0));

  if (!common->endonly)
    compile_char1_matchingpath(common, OP_EODN, cc, backtracks);
  else
    {
    add_jump(compiler, backtracks, CMP(SLJIT_C_LESS, STR_PTR, 0, STR_END, 0));
    check_partial(common, FALSE);
    }
  return cc;

  case OP_DOLLM:
  jump[1] = CMP(SLJIT_C_LESS, STR_PTR, 0, STR_END, 0);
  OP1(SLJIT_MOV, TMP2, 0, ARGUMENTS, 0);
  OP1(SLJIT_MOV_UB, TMP2, 0, SLJIT_MEM1(TMP2), SLJIT_OFFSETOF(jit_arguments, noteol));
  add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP2, 0, SLJIT_IMM, 0));
  check_partial(common, FALSE);
  jump[0] = JUMP(SLJIT_JUMP);
  JUMPHERE(jump[1]);

  if (common->nltype == NLTYPE_FIXED && common->newline > 255)
    {
    OP2(SLJIT_ADD, TMP2, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(2));
    OP1(MOV_UCHAR, TMP1, 0, SLJIT_MEM1(STR_PTR), IN_UCHARS(0));
    if (common->mode == JIT_COMPILE)
      add_jump(compiler, backtracks, CMP(SLJIT_C_GREATER, TMP2, 0, STR_END, 0));
    else
      {
      jump[1] = CMP(SLJIT_C_LESS_EQUAL, TMP2, 0, STR_END, 0);
      /* STR_PTR = STR_END - IN_UCHARS(1) */
      add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, (common->newline >> 8) & 0xff));
      check_partial(common, TRUE);
      add_jump(compiler, backtracks, JUMP(SLJIT_JUMP));
      JUMPHERE(jump[1]);
      }

    OP1(MOV_UCHAR, TMP2, 0, SLJIT_MEM1(STR_PTR), IN_UCHARS(1));
    add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, (common->newline >> 8) & 0xff));
    add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP2, 0, SLJIT_IMM, common->newline & 0xff));
    }
  else
    {
    peek_char(common, common->nlmax);
    check_newlinechar(common, common->nltype, backtracks, FALSE);
    }
  JUMPHERE(jump[0]);
  return cc;

  case OP_CHAR:
  case OP_CHARI:
  length = 1;
#ifdef SUPPORT_UTF
  if (common->utf && HAS_EXTRALEN(*cc)) length += GET_EXTRALEN(*cc);
#endif
  if (common->mode == JIT_COMPILE && (type == OP_CHAR || !char_has_othercase(common, cc) || char_get_othercase_bit(common, cc) != 0))
    {
    OP2(SLJIT_ADD, STR_PTR, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(length));
    add_jump(compiler, backtracks, CMP(SLJIT_C_GREATER, STR_PTR, 0, STR_END, 0));

    context.length = IN_UCHARS(length);
    context.sourcereg = -1;
#if defined SLJIT_UNALIGNED && SLJIT_UNALIGNED
    context.ucharptr = 0;
#endif
    return byte_sequence_compare(common, type == OP_CHARI, cc, &context, backtracks);
    }

  detect_partial_match(common, backtracks);
#ifdef SUPPORT_UTF
  if (common->utf)
    {
    GETCHAR(c, cc);
    }
  else
#endif
    c = *cc;

  if (type == OP_CHAR || !char_has_othercase(common, cc))
    {
    read_char_range(common, c, c, FALSE);
    add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, c));
    return cc + length;
    }
  oc = char_othercase(common, c);
  read_char_range(common, c < oc ? c : oc, c > oc ? c : oc, FALSE);
  bit = c ^ oc;
  if (is_powerof2(bit))
    {
    OP2(SLJIT_OR, TMP1, 0, TMP1, 0, SLJIT_IMM, bit);
    add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, c | bit));
    return cc + length;
    }
  jump[0] = CMP(SLJIT_C_EQUAL, TMP1, 0, SLJIT_IMM, c);
  add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, TMP1, 0, SLJIT_IMM, oc));
  JUMPHERE(jump[0]);
  return cc + length;

  case OP_NOT:
  case OP_NOTI:
  detect_partial_match(common, backtracks);
  length = 1;
#ifdef SUPPORT_UTF
  if (common->utf)
    {
#ifdef COMPILE_PCRE8
    c = *cc;
    if (c < 128)
      {
      OP1(SLJIT_MOV_UB, TMP1, 0, SLJIT_MEM1(STR_PTR), 0);
      if (type == OP_NOT || !char_has_othercase(common, cc))
        add_jump(compiler, backtracks, CMP(SLJIT_C_EQUAL, TMP1, 0, SLJIT_IMM, c));
      else
        {
        /* Since UTF8 code page is fixed, we know that c is in [a-z] or [A-Z] range. */
        OP2(SLJIT_OR, TMP2, 0, TMP1, 0, SLJIT_IMM, 0x20);
        add_jump(compiler, backtracks, CMP(SLJIT_C_EQUAL, TMP2, 0, SLJIT_IMM, c | 0x20));
        }
      /* Skip the variable-length character. */
      OP2(SLJIT_ADD, STR_PTR, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(1));
      jump[0] = CMP(SLJIT_C_LESS, TMP1, 0, SLJIT_IMM, 0xc0);
      OP1(MOV_UCHAR, TMP1, 0, SLJIT_MEM1(TMP1), (sljit_sw)PRIV(utf8_table4) - 0xc0);
      OP2(SLJIT_ADD, STR_PTR, 0, STR_PTR, 0, TMP1, 0);
      JUMPHERE(jump[0]);
      return cc + 1;
      }
    else
#endif /* COMPILE_PCRE8 */
      {
      GETCHARLEN(c, cc, length);
      }
    }
  else
#endif /* SUPPORT_UTF */
    c = *cc;

  if (type == OP_NOT || !char_has_othercase(common, cc))
    {
    read_char_range(common, c, c, TRUE);
    add_jump(compiler, backtracks, CMP(SLJIT_C_EQUAL, TMP1, 0, SLJIT_IMM, c));
    }
  else
    {
    oc = char_othercase(common, c);
    read_char_range(common, c < oc ? c : oc, c > oc ? c : oc, TRUE);
    bit = c ^ oc;
    if (is_powerof2(bit))
      {
      OP2(SLJIT_OR, TMP1, 0, TMP1, 0, SLJIT_IMM, bit);
      add_jump(compiler, backtracks, CMP(SLJIT_C_EQUAL, TMP1, 0, SLJIT_IMM, c | bit));
      }
    else
      {
      add_jump(compiler, backtracks, CMP(SLJIT_C_EQUAL, TMP1, 0, SLJIT_IMM, c));
      add_jump(compiler, backtracks, CMP(SLJIT_C_EQUAL, TMP1, 0, SLJIT_IMM, oc));
      }
    }
  return cc + length;

  case OP_CLASS:
  case OP_NCLASS:
  detect_partial_match(common, backtracks);

#if defined SUPPORT_UTF && defined COMPILE_PCRE8
  bit = (common->utf && is_char7_bitset((const pcre_uint8 *)cc, type == OP_NCLASS)) ? 127 : 255;
  read_char_range(common, 0, bit, type == OP_NCLASS);
#else
  read_char_range(common, 0, 255, type == OP_NCLASS);
#endif

  if (check_class_ranges(common, (const pcre_uint8 *)cc, type == OP_NCLASS, FALSE, backtracks))
    return cc + 32 / sizeof(pcre_uchar);

#if defined SUPPORT_UTF && defined COMPILE_PCRE8
  jump[0] = NULL;
  if (common->utf)
    {
    jump[0] = CMP(SLJIT_C_GREATER, TMP1, 0, SLJIT_IMM, bit);
    if (type == OP_CLASS)
      {
      add_jump(compiler, backtracks, jump[0]);
      jump[0] = NULL;
      }
    }
#elif !defined COMPILE_PCRE8
  jump[0] = CMP(SLJIT_C_GREATER, TMP1, 0, SLJIT_IMM, 255);
  if (type == OP_CLASS)
    {
    add_jump(compiler, backtracks, jump[0]);
    jump[0] = NULL;
    }
#endif /* SUPPORT_UTF && COMPILE_PCRE8 */

  OP2(SLJIT_AND, TMP2, 0, TMP1, 0, SLJIT_IMM, 0x7);
  OP2(SLJIT_LSHR, TMP1, 0, TMP1, 0, SLJIT_IMM, 3);
  OP1(SLJIT_MOV_UB, TMP1, 0, SLJIT_MEM1(TMP1), (sljit_sw)cc);
  OP2(SLJIT_SHL, TMP2, 0, SLJIT_IMM, 1, TMP2, 0);
  OP2(SLJIT_AND | SLJIT_SET_E, SLJIT_UNUSED, 0, TMP1, 0, TMP2, 0);
  add_jump(compiler, backtracks, JUMP(SLJIT_C_ZERO));

#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
  if (jump[0] != NULL)
    JUMPHERE(jump[0]);
#endif

  return cc + 32 / sizeof(pcre_uchar);

#if defined SUPPORT_UTF || defined COMPILE_PCRE16 || defined COMPILE_PCRE32
  case OP_XCLASS:
  compile_xclass_matchingpath(common, cc + LINK_SIZE, backtracks);
  return cc + GET(cc, 0) - 1;
#endif

  case OP_REVERSE:
  length = GET(cc, 0);
  if (length == 0)
    return cc + LINK_SIZE;
  OP1(SLJIT_MOV, TMP1, 0, ARGUMENTS, 0);
#ifdef SUPPORT_UTF
  if (common->utf)
    {
    OP1(SLJIT_MOV, TMP3, 0, SLJIT_MEM1(TMP1), SLJIT_OFFSETOF(jit_arguments, begin));
    OP1(SLJIT_MOV, TMP2, 0, SLJIT_IMM, length);
    label = LABEL();
    add_jump(compiler, backtracks, CMP(SLJIT_C_LESS_EQUAL, STR_PTR, 0, TMP3, 0));
    skip_char_back(common);
    OP2(SLJIT_SUB | SLJIT_SET_E, TMP2, 0, TMP2, 0, SLJIT_IMM, 1);
    JUMPTO(SLJIT_C_NOT_ZERO, label);
    }
  else
#endif
    {
    OP1(SLJIT_MOV, TMP1, 0, SLJIT_MEM1(TMP1), SLJIT_OFFSETOF(jit_arguments, begin));
    OP2(SLJIT_SUB, STR_PTR, 0, STR_PTR, 0, SLJIT_IMM, IN_UCHARS(length));
    add_jump(compiler, backtracks, CMP(SLJIT_C_LESS, STR_PTR, 0, TMP1, 0));
    }
  check_start_used_ptr(common);
  return cc + LINK_SIZE;
  }
