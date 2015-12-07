switch (enc) 
    {
        default:
        case TENC_RAW:    x = strdup(str);   break;
#ifdef HAVE_ICONV
        case TENC_LATIN1: x = toLatin1(str); break;
        case TENC_UCS2:   x = toUcs2(str);   break;
#endif
    }
