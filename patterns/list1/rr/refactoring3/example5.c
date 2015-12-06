switch (unit) {
    case 1:
      __asm__("repne scasb\n\t" : "=D"(end) : "a"(a), "D"(s), "c"(size));
      break;
    case 2:
      __asm__("repne scasw\n\t" : "=D"(end) : "a"(a), "D"(s), "c"(size));
      break;
    case 4:
      __asm__("repne scasl\n\t" : "=D"(end) : "a"(a), "D"(s), "c"(size));
      break;
#ifdef __x86_64__
    case 8:
      __asm__("repne scasq\n\t" : "=D"(end) : "a"(a), "D"(s), "c"(size));
      break;
#endif
  }
