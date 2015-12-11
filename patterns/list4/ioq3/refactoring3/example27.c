switch (pass_mode) {
  case JBUF_PASS_THRU:
    if (cinfo->upsample->need_context_rows) {
      main_ptr->pub.process_data = process_data_context_main;
      make_funny_pointers(cinfo); /* Create the xbuffer[] lists */
      main_ptr->whichptr = 0;	/* Read first iMCU row into xbuffer[0] */
      main_ptr->context_state = CTX_PREPARE_FOR_IMCU;
      main_ptr->iMCU_row_ctr = 0;
    } else {
      /* Simple case with no context needed */
      main_ptr->pub.process_data = process_data_simple_main;
    }
    main_ptr->buffer_full = FALSE;	/* Mark buffer empty */
    main_ptr->rowgroup_ctr = 0;
    break;
#ifdef QUANT_2PASS_SUPPORTED
  case JBUF_CRANK_DEST:
    /* For last pass of 2-pass quantization, just crank the postprocessor */
    main_ptr->pub.process_data = process_data_crank_post;
    break;
#endif
  default:
    ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    break;
  }
