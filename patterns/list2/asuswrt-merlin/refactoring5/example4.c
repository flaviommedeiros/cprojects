#ifndef __powerpc64__
if (memaddr >> 32)
    {
      unsigned long long addr_8 = (unsigned long long) memaddr;
      ptrace (PPC_PTRACE_PEEKTEXT_3264, tid, (PTRACE_TYPE_ARG3) &addr_8, word);
    }
  else
#endif
    *word = ptrace (PT_READ_I, tid, (PTRACE_TYPE_ARG3) (size_t) memaddr, 0);
