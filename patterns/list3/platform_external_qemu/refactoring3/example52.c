switch (cinfo->dct_method) {
#ifdef ANDROID_ARMV6_IDCT
      case JDCT_ISLOW:
      case JDCT_IFAST:
	method_ptr = jpeg_idct_armv6;
	method = JDCT_IFAST;
	break;
#else /* ANDROID_ARMV6_IDCT */
#ifdef DCT_ISLOW_SUPPORTED
      case JDCT_ISLOW:
	method_ptr = jpeg_idct_islow;
	method = JDCT_ISLOW;
	break;
#endif
#ifdef DCT_IFAST_SUPPORTED
      case JDCT_IFAST:
	method_ptr = jpeg_idct_ifast;
	method = JDCT_IFAST;
	break;
#endif
#endif /* ANDROID_ARMV6_IDCT */
#ifdef DCT_FLOAT_SUPPORTED
      case JDCT_FLOAT:
	method_ptr = jpeg_idct_float;
	method = JDCT_FLOAT;
	break;
#endif
      default:
	ERREXIT(cinfo, JERR_NOT_COMPILED);
	break;
      }
