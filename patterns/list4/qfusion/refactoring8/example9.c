static AF_ScriptClass const  af_script_classes[] =
  {
    &af_dummy_script_class,
#ifdef FT_OPTION_AUTOFIT2
    &af_latin2_script_class,
#endif
    &af_latin_script_class,
    &af_cjk_script_class,
    &af_indic_script_class, 
    NULL  /* do not remove */
  };
