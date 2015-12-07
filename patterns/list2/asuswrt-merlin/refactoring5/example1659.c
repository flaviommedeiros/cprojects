#ifdef RE_ENABLE_I18N
if (node->type == COMPLEX_BRACKET && node->duplicated == 0)
    free_charset (node->opr.mbcset);
  else
#endif /* RE_ENABLE_I18N */
    if (node->type == SIMPLE_BRACKET && node->duplicated == 0)
      re_free (node->opr.sbcset);
