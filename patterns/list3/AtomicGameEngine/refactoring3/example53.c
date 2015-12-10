switch(c)
              {
              default: RRETURN(MATCH_NOMATCH);
              case CHAR_CR:
              if (eptr < md->end_subject && UCHAR21(eptr) == CHAR_LF) eptr++;
              break;

              case CHAR_LF:
              break;

              case CHAR_VT:
              case CHAR_FF:
              case CHAR_NEL:
#ifndef EBCDIC
              case 0x2028:
              case 0x2029:
#endif  /* Not EBCDIC */
              if (md->bsr_anycrlf) RRETURN(MATCH_NOMATCH);
              break;
              }
