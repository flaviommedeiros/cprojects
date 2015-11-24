switch (unit) {
    case 1:
      __asm__("rep movsb\n\t" ::"S"(src), "c"(size), "D"(dest));
      break;
    case 2:
      __asm__("rep movsw\n\t" ::"S"(src), "c"(size), "D"(dest));
      break;
    case 4:
      __asm__("rep movsl\n\t" ::"S"(src), "c"(size), "D"(dest));
      break;
#ifdef __x86_64__
    case 8:
      __asm__("rep movsq\n\t" ::"S"(src), "c"(size), "D"(dest));
      break;
#endif
  }
