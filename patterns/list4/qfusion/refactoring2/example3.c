#ifdef FT_CONFIG_OPTION_INCREMENTAL
if ( !face->root.internal->incremental_interface )
#endif
      if ( !loader.charstrings.init )
      {
        FT_ERROR(( "T1_Open_Face: no `/CharStrings' array in face\n" ));
        error = T1_Err_Invalid_File_Format;
      }
