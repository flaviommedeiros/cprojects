switch(c)
        {
        case CHAR_VT:
        case CHAR_FF:
        case CHAR_NEL:
#ifndef EBCDIC
        case 0x2028:
        case 0x2029:
#endif  /* Not EBCDIC */
        if ((md->moptions & PCRE_BSR_ANYCRLF) != 0) break;

        case CHAR_LF:
        ADD_NEW(state_offset + 1, 0);
        break;

        case CHAR_CR:
        if (ptr + 1 >= end_subject)
          {
          ADD_NEW(state_offset + 1, 0);
          if ((md->moptions & PCRE_PARTIAL_HARD) != 0)
            reset_could_continue = TRUE;
          }
        else if (UCHAR21TEST(ptr + 1) == CHAR_LF)
          {
          ADD_NEW_DATA(-(state_offset + 1), 0, 1);
          }
        else
          {
          ADD_NEW(state_offset + 1, 0);
          }
        break;
        }
