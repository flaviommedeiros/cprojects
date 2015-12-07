#ifdef COMPILE_PCRE16
if (c > (utf ? 0x10ffff : 0xffff))
#endif
#endif
          {
          *errorcodeptr = ERR76;
          }
        else if (utf && c >= 0xd800 && c <= 0xdfff) *errorcodeptr = ERR73;
