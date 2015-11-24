switch (unit) {
    case 1:
      __asm__("rep stosb\n\t" ::"a"(a), "c"(size), "D"(dest));
      break;
    case 2:
      __asm__("rep stosw\n\t" ::"a"(a), "c"(size), "D"(dest));
      break;
    case 4:
      __asm__("rep stosl\n\t" ::"a"(a), "c"(size), "D"(dest));
      break;
#ifdef __x86_64__
    case 8:
      __asm__("rep stosq\n\t" ::"a"(a), "c"(size), "D"(dest));
      break;
#endif
  }
