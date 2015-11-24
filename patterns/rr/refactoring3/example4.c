switch (unit) {
    case 1:
      __asm__("repe scasb\n\t" : "=D"(end) : "a"(a), "D"(s), "c"(size));
      break;
    case 2:
      __asm__("repe scasw\n\t" : "=D"(end) : "a"(a), "D"(s), "c"(size));
      break;
    case 4:
      __asm__("repe scasl\n\t" : "=D"(end) : "a"(a), "D"(s), "c"(size));
      break;
#ifdef __x86_64__
    case 8:
      __asm__("repe scasq\n\t" : "=D"(end) : "a"(a), "D"(s), "c"(size));
      break;
#endif
  }
