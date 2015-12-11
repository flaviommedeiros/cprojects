#ifdef FT_CONFIG_OPTION_INCREMENTAL
if ( glyph_index >= (FT_UInt)face->num_glyphs &&
         !face->internal->incremental_interface   )
#else
    if ( glyph_index >= (FT_UInt)face->num_glyphs )
#endif
      return TT_Err_Invalid_Argument;
