#ifdef SUPPORT_UTF
if (utf && c > MAX_VALUE_FOR_SINGLE_CHAR)
            code += PRIV(ord2utf)(c, code);
          else
#endif
            *code++ = c;
