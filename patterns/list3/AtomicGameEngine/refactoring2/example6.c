#if defined COMPILE_PCRE8
if (c > (utf ? 0x10ffffU : 0xffU))
#elif defined COMPILE_PCRE16
        if (c > (utf ? 0x10ffffU : 0xffffU))
#elif defined COMPILE_PCRE32
        if (utf && c > 0x10ffffU)
#endif
          {
          *errorcodeptr = ERR76;
          }
        else if (utf && c >= 0xd800 && c <= 0xdfff) *errorcodeptr = ERR73;
