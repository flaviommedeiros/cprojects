switch (c)
          {
          case CHAR_VT:
          case CHAR_FF:
          case CHAR_NEL:
#ifndef EBCDIC
          case 0x2028:
          case 0x2029:
#endif  /* Not EBCDIC */
          if ((md->moptions & PCRE_BSR_ANYCRLF) != 0) break;
          goto ANYNL02;

          case CHAR_CR:
          if (ptr + 1 < end_subject && UCHAR21TEST(ptr + 1) == CHAR_LF) ncount = 1;
          /* Fall through */

          ANYNL02:
          case CHAR_LF:
          if (codevalue == OP_ANYNL_EXTRA + OP_TYPEPOSSTAR ||
              codevalue == OP_ANYNL_EXTRA + OP_TYPEPOSQUERY)
            {
            active_count--;           /* Remove non-match possibility */
            next_active_state--;
            }
          ADD_NEW_DATA(-(state_offset + (int)count), 0, ncount);
          break;

          default:
          break;
          }
