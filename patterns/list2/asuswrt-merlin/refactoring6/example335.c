if (c != 0x09 && c != 0x20 && c != 0xa0
#ifdef COMPILE_PCRE16
              && c != 0x1680 && c != 0x180e && (c < 0x2000 || c > 0x200A)
              && c != 0x202f && c != 0x205f && c != 0x3000
#endif
              ) break;
