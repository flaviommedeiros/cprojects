switch (pass_mode) {
  case JBUF_PASS_THRU:
#ifdef FULL_MAIN_BUFFER_SUPPORTED
    if (main->whole_image[0] != NULL)
      ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
#endif
    main->pub.process_data = process_data_simple_main;
    break;
#ifdef FULL_MAIN_BUFFER_SUPPORTED
  case JBUF_SAVE_SOURCE:
  case JBUF_CRANK_DEST:
  case JBUF_SAVE_AND_PASS:
    if (main->whole_image[0] == NULL)
      ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    main->pub.process_data = process_data_buffer_main;
    break;
#endif
  default:
    ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    break;
  }
