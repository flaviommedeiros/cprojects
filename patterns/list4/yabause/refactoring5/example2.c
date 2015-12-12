#ifdef EXEC_FROM_CACHE
if ((context->regs.PC & 0xC0000000) == 0xC0000000) context->instruction = DataArrayReadWord(context->regs.PC);
      else
#endif
      context->instruction = fetchlist[(context->regs.PC >> 20) & 0x0FF](context->regs.PC);
