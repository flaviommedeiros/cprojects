#ifndef __powerpc64__
if (memaddr >> 32)
    {
      unsigned long long addr_8 = (unsigned long long) memaddr;
      ptrace (PPC_PTRACE_POKEDATA_3264, tid, (PTRACE_TYPE_ARG3) &addr_8, word);
    }
  else
#endif
    ptrace (PT_WRITE_D, tid, (PTRACE_TYPE_ARG3) (size_t) memaddr, word);
