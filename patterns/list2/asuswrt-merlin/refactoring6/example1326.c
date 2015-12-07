if (c != 0x000a && (md->bsr_anycrlf ||
                (c != 0x000b && c != 0x000c && c != 0x0085
#ifdef COMPILE_PCRE16
                && c != 0x2028 && c != 0x2029
#endif
                ))) break;
