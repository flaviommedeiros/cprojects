#ifdef SUPPORT_UCP
if (utf && (options & PCRE_CASELESS) != 0 &&
              (d = UCD_CASESET(c)) != 0)
            {
            *code++ = OP_NOTPROP;
            *code++ = PT_CLIST;
            *code++ = d;
            }
          else
#endif
          /* Char has only one other case, or UCP not available */

            {
            *code++ = ((options & PCRE_CASELESS) != 0)? OP_NOTI: OP_NOT;
#if defined SUPPORT_UTF && !defined COMPILE_PCRE32
            if (utf && c > MAX_VALUE_FOR_SINGLE_CHAR)
              code += PRIV(ord2utf)(c, code);
            else
#endif
              *code++ = c;
            }
