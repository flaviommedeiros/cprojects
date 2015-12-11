#ifdef NEW_DYNAREC
if (r4300emu == CORE_DYNAREC)
         last_addr = pcaddr;
      else
#endif
         jump_to(address);
