#ifdef FT_CONFIG_OPTION_INCREMENTAL
if ( !loader->glyf_offset                        &&
           !face->root.internal->incremental_interface )
#else
      if ( !loader->glyf_offset )
#endif /* FT_CONFIG_OPTION_INCREMENTAL */
      {
        FT_TRACE2(( "no `glyf' table but non-zero `loca' entry\n" ));
        error = FT_THROW( Invalid_Table );
        goto Exit;
      }
