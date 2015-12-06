switch (hash_ext)
   {
#ifdef HAVE_FFMPEG
      case MENU_VALUE_FILE_OGM:
      case MENU_VALUE_FILE_MKV:
      case MENU_VALUE_FILE_AVI:
      case MENU_VALUE_FILE_MP4:
      case MENU_VALUE_FILE_FLV:
      case MENU_VALUE_FILE_WEBM:
      case MENU_VALUE_FILE_3GP:
      case MENU_VALUE_FILE_F4F:
      case MENU_VALUE_FILE_F4V:
      case MENU_VALUE_FILE_MOV:
      case MENU_VALUE_FILE_WMV:
         return RARCH_CONTENT_MOVIE;
      case MENU_VALUE_FILE_MP3:
      case MENU_VALUE_FILE_M4A:
      case MENU_VALUE_FILE_OGG:
      case MENU_VALUE_FILE_FLAC:
      case MENU_VALUE_FILE_WAV:
         return RARCH_CONTENT_MUSIC;
#endif
#ifdef HAVE_IMAGEVIEWER
      case MENU_VALUE_FILE_JPG:
      case MENU_VALUE_FILE_JPG_CAPS:
      case MENU_VALUE_FILE_JPEG:
      case MENU_VALUE_FILE_JPEG_CAPS:
      case MENU_VALUE_FILE_PNG:
      case MENU_VALUE_FILE_PNG_CAPS:
      case MENU_VALUE_FILE_TGA:
      case MENU_VALUE_FILE_BMP:
         return RARCH_CONTENT_IMAGE;
#endif
      case 0:
      default:
         break;
   
