#ifndef COMPILE_PCRE8
if (c > 255)
              {
              if (op == OP_CLASS) break;
              }
            else
#endif
              if ((BYTE_MAP[c/8] & (1 << (c&7))) == 0) break;
