#ifndef __powerpc64__
if (memaddr >> 32)
    {
      uint64_t addr_8 = (uint64_t) memaddr;
      ptrace (PPC_PTRACE_POKEDATA_3264, tid, (PTRACE_TYPE_ARG3) &addr_8, word);
    }
  else
#endif
    ptrace (PT_WRITE_D, tid, (PTRACE_TYPE_ARG3) (size_t) memaddr, word);
