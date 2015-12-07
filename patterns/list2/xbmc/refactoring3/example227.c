switch (enc)
    {
        default:
        case TENC_RAW:
        case TENC_LATIN1: result = set_id3tag(gfp, type, x);   break;
#ifdef HAVE_ICONV
        case TENC_UCS2:   result = set_id3v2tag(gfp, type, x); break;
#endif
    }
