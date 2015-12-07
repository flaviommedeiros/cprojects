#ifdef FT_CONFIG_OPTION_INCREMENTAL
if ( face->root.internal->incremental_interface )
      loader->glyf_offset = 0;
    else

#endif

    {
      FT_Error  error = face->goto_table( face, TTAG_glyf, stream, 0 );


      if ( error == TT_Err_Table_Missing )
        loader->glyf_offset = 0;
      else if ( error )
      {
        FT_ERROR(( "TT_Load_Glyph: could not access glyph table\n" ));
        return error;
      }
      else
        loader->glyf_offset = FT_STREAM_POS();
    }
