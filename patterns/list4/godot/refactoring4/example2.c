#ifdef FT_CONFIG_OPTION_INCREMENTAL
if ( glyph_index >= (FT_UInt)face->root.num_glyphs &&
         !face->root.internal->incremental_interface   )
#else
    if ( glyph_index >= (FT_UInt)face->root.num_glyphs )
#endif /* FT_CONFIG_OPTION_INCREMENTAL */
    {
      error = FT_THROW( Invalid_Argument );
      goto Exit;
    }
