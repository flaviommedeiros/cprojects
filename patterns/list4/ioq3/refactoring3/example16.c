switch (cinfo->dct_method) {
#ifdef DCT_ISLOW_SUPPORTED
      case JDCT_ISLOW:
	fdct->do_dct[ci] = jpeg_fdct_islow;
	method = JDCT_ISLOW;
	break;
#endif
#ifdef DCT_IFAST_SUPPORTED
      case JDCT_IFAST:
	fdct->do_dct[ci] = jpeg_fdct_ifast;
	method = JDCT_IFAST;
	break;
#endif
#ifdef DCT_FLOAT_SUPPORTED
      case JDCT_FLOAT:
	fdct->do_float_dct[ci] = jpeg_fdct_float;
	method = JDCT_FLOAT;
	break;
#endif
      default:
	ERREXIT(cinfo, JERR_NOT_COMPILED);
	break;
      }
