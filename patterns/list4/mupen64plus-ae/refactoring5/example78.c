#ifndef TT_CONFIG_OPTION_SUBPIXEL_HINTING
if ( *interpreter_version != TT_INTERPRETER_VERSION_35 )
        error = FT_ERR( Unimplemented_Feature );
      else
#endif
        driver->interpreter_version = *interpreter_version;
