#if ___WCHAR_MIN < 0 || ___WCHAR_MAX > ___MAX_CHR
if (c < 0 || c > ___MAX_CHR)
#else
                if (c < 0)
#endif
#else
                if (c > ___MAX_CHR)
#endif
                  {
                    ___release_scmobj (result);
                    *obj = ___FAL;
                    return ___FIX(___CTOS_NONNULLWCHARSTRING_ERR+arg_num);
                  }
