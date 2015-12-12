switch (chr)
        {
        case CHAR_CR:
        case CHAR_LF:
        case CHAR_VT:
        case CHAR_FF:
        case CHAR_NEL:
#ifndef EBCDIC
        case 0x2028:
        case 0x2029:
#endif  /* Not EBCDIC */
        return FALSE;
        }
