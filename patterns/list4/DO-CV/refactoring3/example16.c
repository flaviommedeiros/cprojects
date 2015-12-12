switch (pass_mode) {
  case JBUF_PASS_THRU:
    if (cinfo->upsample->need_context_rows) {
      mainp->pub.process_data = process_data_context_main;
      make_funny_pointers(cinfo); /* Create the xbuffer[] lists */
      mainp->whichptr = 0;	/* Read first iMCU row into xbuffer[0] */
      mainp->context_state = CTX_PREPARE_FOR_IMCU;
      mainp->iMCU_row_ctr = 0;
    } else {
      /* Simple case with no context needed */
      mainp->pub.process_data = process_data_simple_main;
    }
    mainp->buffer_full = FALSE;	/* Mark buffer empty */
    mainp->rowgroup_ctr = 0;
    break;
#ifdef QUANT_2PASS_SUPPORTED
  case JBUF_CRANK_DEST:
    /* For last pass of 2-pass quantization, just crank the postprocessor */
    mainp->pub.process_data = process_data_crank_post;
    break;
#endif
  default:
    ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    break;
  }
