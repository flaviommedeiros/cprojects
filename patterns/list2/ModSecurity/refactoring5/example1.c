#ifdef ACMP_USE_UTF8
if (parser->is_utf8) {
        for (i = 0; i < len; i++) {
            *(ucs_chars++) = utf8_decodechar(c);
            c += utf8_seq_len(c);
        }
    } else
#endif
    {
        for (i = 0; i < len; i++) {
            *(ucs_chars++) = *(c++);
        }
    }
