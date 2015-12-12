if (c != CHAR_LF && (md->bsr_anycrlf ||
                 (c != CHAR_VT && c != CHAR_FF && c != CHAR_NEL
#if defined COMPILE_PCRE16 || defined COMPILE_PCRE32
                 && c != 0x2028 && c != 0x2029
#endif
                 ))) break;
