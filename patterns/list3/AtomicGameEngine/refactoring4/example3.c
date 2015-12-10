#ifdef FT_CONFIG_OPTION_INCREMENTAL
if ( decoder->glyph_names == 0                   &&
         !face->root.internal->incremental_interface )
#else
    if ( decoder->glyph_names == 0 )
#endif /* FT_CONFIG_OPTION_INCREMENTAL */
    {
      FT_ERROR(( "t1operator_seac:"
                 " glyph names table not available in this font\n" ));
      return FT_THROW( Syntax_Error );
    }
