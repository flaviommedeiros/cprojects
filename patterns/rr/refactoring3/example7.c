switch (unit) {
    case 1:
      __asm__("repne cmpsb\n\t" : "=D"(sp) : "S"(tp), "D"(s), "c"(size));
      break;
    case 2:
      __asm__("repne cmpsw\n\t" : "=D"(sp) : "S"(tp), "D"(s), "c"(size));
      break;
    case 4:
      __asm__("repne cmpsl\n\t" : "=D"(sp) : "S"(tp), "D"(s), "c"(size));
      break;
#ifdef __x86_64__
    case 8:
      __asm__("repne cmpsq\n\t" : "=D"(sp) : "S"(tp), "D"(s), "c"(size));
      break;
#endif
  }
