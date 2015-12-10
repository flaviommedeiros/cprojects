#ifdef TT_CONFIG_OPTION_SUBPIXEL_HINTING
if ( driver->interpreter_version == TT_INTERPRETER_VERSION_38 )
      {
        /* scale, but only if enabled and only if TT hinting is being used */
        if ( IS_HINTED( loader->load_flags ) )
          x_scale_factor = sph_test_tweak_x_scaling( face,
                                                     family,
                                                     ppem,
                                                     style,
                                                     loader->glyph_index );
        /* scale the glyph */
        if ( ( loader->load_flags & FT_LOAD_NO_SCALE ) == 0 ||
             x_scale_factor != 1000                         )
        {
          x_scale = FT_MulDiv( ((TT_Size)loader->size)->metrics.x_scale,
                               x_scale_factor, 1000 );
          y_scale = ((TT_Size)loader->size)->metrics.y_scale;

          /* compensate for any scaling by de/emboldening; */
          /* the amount was determined via experimentation */
          if ( x_scale_factor != 1000 && ppem > 11 )
            FT_Outline_EmboldenXY( outline,
                                   FT_MulFix( 1280 * ppem,
                                              1000 - x_scale_factor ),
                                   0 );
          do_scale = TRUE;
        }
      }
      else

#endif /* TT_CONFIG_OPTION_SUBPIXEL_HINTING */

      {
        /* scale the glyph */
        if ( ( loader->load_flags & FT_LOAD_NO_SCALE ) == 0 )
        {
          x_scale = ((TT_Size)loader->size)->metrics.x_scale;
          y_scale = ((TT_Size)loader->size)->metrics.y_scale;

          do_scale = TRUE;
        }
      }
