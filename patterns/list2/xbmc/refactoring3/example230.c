switch(extend_type)
    {
      case EXTEND_MSDOS:
	msdos_to_unix_filename(filename, name_length);
      case EXTEND_HUMAN:
	; /* ignored */
	break;

#ifdef OSK
      case EXTEND_OS68K:
      case EXTEND_XOSK:
#endif
      case EXTEND_UNIX:
	break;

      case EXTEND_MACOS:
	macos_to_unix_filename(filename, name_length);
	break;

      default:
	generic_to_unix_filename(filename, name_length);
    }
