switch (cinfo->dct_method) {
#ifdef DCT_ISLOW_SUPPORTED
  case JDCT_ISLOW:
    fdct->pub.forward_DCT = forward_DCT;
    fdct->do_dct = jpeg_fdct_islow;
    break;
#endif
#ifdef DCT_IFAST_SUPPORTED
  case JDCT_IFAST:
    fdct->pub.forward_DCT = forward_DCT;
    fdct->do_dct = jpeg_fdct_ifast;
    break;
#endif
#ifdef DCT_FLOAT_SUPPORTED
  case JDCT_FLOAT:
    fdct->pub.forward_DCT = forward_DCT_float;
    fdct->do_float_dct = jpeg_fdct_float;
    break;
#endif
  default:
    ERREXIT(cinfo, JERR_NOT_COMPILED);
    break;
  }
