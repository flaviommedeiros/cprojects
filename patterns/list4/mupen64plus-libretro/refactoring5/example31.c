#ifdef NEW_DYNAREC
if (r4300emu == CORE_DYNAREC)
   {
      g_cp0_regs[CP0_EPC_REG] = pcaddr;
      pcaddr = 0x80000180;
      g_cp0_regs[CP0_STATUS_REG] |= UINT32_C(2);
      g_cp0_regs[CP0_CAUSE_REG] &= UINT32_C(0x7FFFFFFF);
      pending_exception=1;
   }
   else
#endif
      exception_general();
