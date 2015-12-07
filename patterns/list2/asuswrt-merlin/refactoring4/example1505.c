#ifndef CHARSET_EBCDIC
if (*p == '+')
#else
        if (*p == os_toascii['+'])
#endif
        {
            p++;
            mval = -1;
        } else
            mval = 0;
