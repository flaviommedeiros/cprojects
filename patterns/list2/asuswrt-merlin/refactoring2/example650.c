#if defined SUPPORT_UTF || !defined COMPILE_PCRE8
if (common->utf)
#endif /* COMPILE_PCRE8 */
    {
    jump[0] = CMP(SLJIT_C_GREATER, TMP1, 0, SLJIT_IMM, 255);
    if (type == OP_CLASS)
      {
      add_jump(compiler, backtracks, jump[0]);
      jump[0] = NULL;
      }
    }
