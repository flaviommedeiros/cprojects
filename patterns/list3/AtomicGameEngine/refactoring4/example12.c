#if defined COMPILE_PCRE8
if (context->ucharptr >= 4 || context->length == 0 || (context->ucharptr == 2 && context->length == 1))
#else
  if (context->ucharptr >= 2 || context->length == 0)
#endif
    {
    if (context->length >= 4)
      OP1(SLJIT_MOV_SI, context->sourcereg, 0, SLJIT_MEM1(STR_PTR), -context->length);
    else if (context->length >= 2)
      OP1(SLJIT_MOV_UH, context->sourcereg, 0, SLJIT_MEM1(STR_PTR), -context->length);
#if defined COMPILE_PCRE8
    else if (context->length >= 1)
      OP1(SLJIT_MOV_UB, context->sourcereg, 0, SLJIT_MEM1(STR_PTR), -context->length);
#endif /* COMPILE_PCRE8 */
    context->sourcereg = context->sourcereg == TMP1 ? TMP2 : TMP1;

    switch(context->ucharptr)
      {
      case 4 / sizeof(pcre_uchar):
      if (context->oc.asint != 0)
        OP2(SLJIT_OR, context->sourcereg, 0, context->sourcereg, 0, SLJIT_IMM, context->oc.asint);
      add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, context->sourcereg, 0, SLJIT_IMM, context->c.asint | context->oc.asint));
      break;

      case 2 / sizeof(pcre_uchar):
      if (context->oc.asushort != 0)
        OP2(SLJIT_OR, context->sourcereg, 0, context->sourcereg, 0, SLJIT_IMM, context->oc.asushort);
      add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, context->sourcereg, 0, SLJIT_IMM, context->c.asushort | context->oc.asushort));
      break;

#ifdef COMPILE_PCRE8
      case 1:
      if (context->oc.asbyte != 0)
        OP2(SLJIT_OR, context->sourcereg, 0, context->sourcereg, 0, SLJIT_IMM, context->oc.asbyte);
      add_jump(compiler, backtracks, CMP(SLJIT_C_NOT_EQUAL, context->sourcereg, 0, SLJIT_IMM, context->c.asbyte | context->oc.asbyte));
      break;
#endif

      default:
      SLJIT_ASSERT_STOP();
      break;
      }
    context->ucharptr = 0;
    }
