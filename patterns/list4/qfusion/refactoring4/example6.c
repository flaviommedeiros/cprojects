#ifdef AF_CONFIG_OPTION_USE_WARPER
if ( metrics->root.scaler.render_mode == FT_RENDER_MODE_LIGHT ||
         AF_HINTS_DO_HORIZONTAL( hints ) )
#else
    if ( AF_HINTS_DO_HORIZONTAL( hints ) )
#endif
    {
      error = af_latin2_hints_detect_features( hints, AF_DIMENSION_HORZ );
      if ( error )
        goto Exit;
    }
