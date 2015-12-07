#ifndef __powerpc64__
if (memaddr >> 32)
    {
      uint64_t addr_8 = (uint64_t) memaddr;
      ptrace (PPC_PTRACE_PEEKTEXT_3264, tid, (PTRACE_TYPE_ARG3) &addr_8, word);
    }
  else
#endif
    *word = ptrace (PT_READ_I, tid, (PTRACE_TYPE_ARG3) (size_t) memaddr, 0);
