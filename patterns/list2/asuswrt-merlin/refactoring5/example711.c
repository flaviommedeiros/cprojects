#ifdef SUPPORT_UCP
if (-c >= ESC_DU && -c <= ESC_wu)
          {
          nestptr = ptr + 1;                   /* Where to resume */
          ptr = substitutes[-c - ESC_DU] - 1;  /* Just before substitute */
          }
        else
#endif
        /* In non-UTF-8 mode, we turn \C into OP_ALLANY instead of OP_ANYBYTE
        so that it works in DFA mode and in lookbehinds. */

          {
          previous = (-c > ESC_b && -c < ESC_Z)? code : NULL;
          *code++ = (!utf && c == -ESC_C)? OP_ALLANY : -c;
          }
