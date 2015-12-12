if (c == 0
#if 0 < ___WCHAR_MIN
                || c < ___WCHAR_MIN
#endif
#if ___MAX_CHR > ___WCHAR_MAX
                || c > ___WCHAR_MAX
#endif
                )
              {
                ___release_rc (r);
                return ___FIX(___STOC_WCHARSTRING_ERR+arg_num);
              }
