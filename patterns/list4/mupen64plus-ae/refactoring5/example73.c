#ifdef FT_CONFIG_OPTION_INCREMENTAL
if ( face->root.internal->incremental_interface )
    {
      /* the caller must handle the font encoding also */
      bchar_index = bchar;
      achar_index = achar;
    }
    else
#endif
    {
      bchar_index = t1_lookup_glyph_by_stdcharcode( decoder, bchar );
      achar_index = t1_lookup_glyph_by_stdcharcode( decoder, achar );
    }
