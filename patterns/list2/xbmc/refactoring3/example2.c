switch (pass_mode) {
  case JBUF_PASS_THRU:
    if (coef->whole_image[0] != NULL)
      ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    coef->pub.compress_data = compress_data;
    break;
#ifdef FULL_COEF_BUFFER_SUPPORTED
  case JBUF_SAVE_AND_PASS:
    if (coef->whole_image[0] == NULL)
      ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    coef->pub.compress_data = compress_first_pass;
    break;
  case JBUF_CRANK_DEST:
    if (coef->whole_image[0] == NULL)
      ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    coef->pub.compress_data = compress_output;
    break;
#endif
  default:
    ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    break;
  }
