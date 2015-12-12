#if ___WCHAR_MIN < 0 || ___WCHAR_MAX > ___MAX_CHR
if (x < 0 || x > ___MAX_CHR)
#else
  if (x < 0)
#endif
#else
  if (x > ___MAX_CHR)
#endif
    {
      *obj = ___FAL;
      return ___FIX(___CTOS_WCHAR_ERR+arg_num);
    }
