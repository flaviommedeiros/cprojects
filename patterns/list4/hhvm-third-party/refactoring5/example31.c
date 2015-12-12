#ifdef SUPPORT_UCP
if (escape >= ESC_DU && escape <= ESC_wu)
          {
          nestptr = ptr + 1;                   /* Where to resume */
          ptr = substitutes[escape - ESC_DU] - 1;  /* Just before substitute */
          }
        else
#endif
        /* In non-UTF-8 mode, we turn \C into OP_ALLANY instead of OP_ANYBYTE
        so that it works in DFA mode and in lookbehinds. */

          {
          previous = (escape > ESC_b && escape < ESC_Z)? code : NULL;
          *code++ = (!utf && escape == ESC_C)? OP_ALLANY : escape;
          }
