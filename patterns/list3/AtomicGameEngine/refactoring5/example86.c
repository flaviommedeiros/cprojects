#ifdef SUPPORT_UCP
if (common->use_ucp)
  {
  OP1(SLJIT_MOV, TMP2, 0, SLJIT_IMM, 1);
  jump = CMP(SLJIT_C_EQUAL, TMP1, 0, SLJIT_IMM, CHAR_UNDERSCORE);
  add_jump(compiler, &common->getucd, JUMP(SLJIT_FAST_CALL));
  OP2(SLJIT_SUB, TMP1, 0, TMP1, 0, SLJIT_IMM, ucp_Ll);
  OP2(SLJIT_SUB | SLJIT_SET_U, SLJIT_UNUSED, 0, TMP1, 0, SLJIT_IMM, ucp_Lu - ucp_Ll);
  OP_FLAGS(SLJIT_MOV, TMP2, 0, SLJIT_UNUSED, 0, SLJIT_C_LESS_EQUAL);
  OP2(SLJIT_SUB, TMP1, 0, TMP1, 0, SLJIT_IMM, ucp_Nd - ucp_Ll);
  OP2(SLJIT_SUB | SLJIT_SET_U, SLJIT_UNUSED, 0, TMP1, 0, SLJIT_IMM, ucp_No - ucp_Nd);
  OP_FLAGS(SLJIT_OR, TMP2, 0, TMP2, 0, SLJIT_C_LESS_EQUAL);
  JUMPHERE(jump);
  OP1(SLJIT_MOV, SLJIT_MEM1(SLJIT_LOCALS_REG), LOCALS1, TMP2, 0);
  }
else
#endif
  {
#ifndef COMPILE_PCRE8
  jump = CMP(SLJIT_C_GREATER, TMP1, 0, SLJIT_IMM, 255);
#elif defined SUPPORT_UTF
  /* Here LOCALS1 has already been zeroed. */
  jump = NULL;
  if (common->utf)
    jump = CMP(SLJIT_C_GREATER, TMP1, 0, SLJIT_IMM, 255);
#endif /* COMPILE_PCRE8 */
  OP1(SLJIT_MOV_UB, TMP1, 0, SLJIT_MEM1(TMP1), common->ctypes);
  OP2(SLJIT_LSHR, TMP1, 0, TMP1, 0, SLJIT_IMM, 4 /* ctype_word */);
  OP2(SLJIT_AND, TMP1, 0, TMP1, 0, SLJIT_IMM, 1);
  OP1(SLJIT_MOV, SLJIT_MEM1(SLJIT_LOCALS_REG), LOCALS1, TMP1, 0);
#ifndef COMPILE_PCRE8
  JUMPHERE(jump);
#elif defined SUPPORT_UTF
  if (jump != NULL)
    JUMPHERE(jump);
#endif /* COMPILE_PCRE8 */
  }
