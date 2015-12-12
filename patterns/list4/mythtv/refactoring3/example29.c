switch (enc)
    {
        default:
#ifdef ID3TAGS_EXTENDED
        case TENC_LATIN1: result = set_id3tag(gfp, type, x);   break;
        case TENC_UTF16:  result = set_id3v2tag(gfp, type, x); break;
#else
        case TENC_RAW:    result = set_id3tag(gfp, type, x);   break;
#endif
    }
