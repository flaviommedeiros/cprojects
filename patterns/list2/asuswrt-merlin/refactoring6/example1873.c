if (c != 0x0a && c != 0x0b && c != 0x0c && c != 0x0d && c != 0x85
#ifdef COMPILE_PCRE16
              && c != 0x2028 && c != 0x2029
#endif
              ) break;
