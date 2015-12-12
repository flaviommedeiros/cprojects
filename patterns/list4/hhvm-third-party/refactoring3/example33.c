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
