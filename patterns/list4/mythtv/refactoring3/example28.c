switch (enc) 
    {
        default:
#ifdef ID3TAGS_EXTENDED
        case TENC_LATIN1: x = toLatin1(str); break;
        case TENC_UTF16:  x = toUtf16(str);   break;
#else
        case TENC_RAW:    x = strdup(str);   break;
#endif
    }
