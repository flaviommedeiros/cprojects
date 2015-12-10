#ifdef TT_CONFIG_OPTION_SUBPIXEL_HINTING
if ( driver->interpreter_version == TT_INTERPRETER_VERSION_38 )
      {
        FT_Bool  ignore_x_mode;


        ignore_x_mode = FT_BOOL( FT_LOAD_TARGET_MODE( loader->load_flags ) !=
                                 FT_RENDER_MODE_MONO );

        if ( widthp                                                   &&
             ( ( ignore_x_mode && loader->exec->compatible_widths ) ||
                !ignore_x_mode                                      ||
                SPH_OPTION_BITMAP_WIDTHS                            ) )
          glyph->metrics.horiAdvance = *widthp << 6;
      }
      else

#endif /* TT_CONFIG_OPTION_SUBPIXEL_HINTING */

      {
        if ( widthp )
          glyph->metrics.horiAdvance = *widthp << 6;
      }
