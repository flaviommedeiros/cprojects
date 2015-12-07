#ifdef RE_ENABLE_I18N
if (BE (sbcset == NULL || mbcset == NULL, 0))
#else
  if (BE (sbcset == NULL, 0))
#endif /* RE_ENABLE_I18N */
    {
      re_free (sbcset);
#ifdef RE_ENABLE_I18N
      re_free (mbcset);
#endif
      *err = REG_ESPACE;
      return NULL;
    }
