#ifndef CFF_CONFIG_OPTION_OLD_ENGINE
if ( *hinting_engine != FT_CFF_HINTING_ADOBE )
        error = FT_ERR( Unimplemented_Feature );
      else
#endif
        driver->hinting_engine = *hinting_engine;
