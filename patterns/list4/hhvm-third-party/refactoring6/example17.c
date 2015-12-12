if (c != CHAR_LF &&
                  (md->bsr_anycrlf ||
                   (c != CHAR_VT && c != CHAR_FF && c != CHAR_NEL
#ifndef EBCDIC
                    && c != 0x2028 && c != 0x2029
#endif  /* Not EBCDIC */
                    )))
                break;
