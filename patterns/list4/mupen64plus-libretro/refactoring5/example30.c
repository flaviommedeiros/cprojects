#ifdef NEW_DYNAREC
if (r4300emu == CORE_DYNAREC)
   {
      pcaddr = pc;
      pending_exception = 1;
      invalidate_all_pages();
   }
   else
#endif
   {
      generic_jump_to(pc);
      invalidate_r4300_cached_code(0,0);
   }
