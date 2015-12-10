switch (master->pass_type) {
  case main_pass:
    /* Initial pass: will collect input data, and do either Huffman
     * optimization or data output for the first scan.
     */
    select_scan_parameters(cinfo);
    per_scan_setup(cinfo);
    if (! cinfo->raw_data_in) {
      (*cinfo->cconvert->start_pass) (cinfo);
      (*cinfo->downsample->start_pass) (cinfo);
      (*cinfo->prep->start_pass) (cinfo, JBUF_PASS_THRU);
    }
    (*cinfo->fdct->start_pass) (cinfo);
    (*cinfo->entropy->start_pass) (cinfo, cinfo->optimize_coding);
    (*cinfo->coef->start_pass) (cinfo,
				(master->total_passes > 1 ?
				 JBUF_SAVE_AND_PASS : JBUF_PASS_THRU));
    (*cinfo->main->start_pass) (cinfo, JBUF_PASS_THRU);
    if (cinfo->optimize_coding) {
      /* No immediate data output; postpone writing frame/scan headers */
      master->pub.call_pass_startup = FALSE;
    } else {
      /* Will write frame/scan headers at first jpeg_write_scanlines call */
      master->pub.call_pass_startup = TRUE;
    }
    break;
#ifdef ENTROPY_OPT_SUPPORTED
  case huff_opt_pass:
    /* Do Huffman optimization for a scan after the first one. */
    select_scan_parameters(cinfo);
    per_scan_setup(cinfo);
    if (cinfo->Ss != 0 || cinfo->Ah == 0 || cinfo->arith_code) {
      (*cinfo->entropy->start_pass) (cinfo, TRUE);
      (*cinfo->coef->start_pass) (cinfo, JBUF_CRANK_DEST);
      master->pub.call_pass_startup = FALSE;
      break;
    }
    /* Special case: Huffman DC refinement scans need no Huffman table
     * and therefore we can skip the optimization pass for them.
     */
    master->pass_type = output_pass;
    master->pass_number++;
    /*FALLTHROUGH*/
#endif
  case output_pass:
    /* Do a data-output pass. */
    /* We need not repeat per-scan setup if prior optimization pass did it. */
    if (! cinfo->optimize_coding) {
      select_scan_parameters(cinfo);
      per_scan_setup(cinfo);
    }
    (*cinfo->entropy->start_pass) (cinfo, FALSE);
    (*cinfo->coef->start_pass) (cinfo, JBUF_CRANK_DEST);
    /* We emit frame/scan headers now */
    if (master->scan_number == 0)
      (*cinfo->marker->write_frame_header) (cinfo);
    (*cinfo->marker->write_scan_header) (cinfo);
    master->pub.call_pass_startup = FALSE;
    break;
  default:
    ERREXIT(cinfo, JERR_NOT_COMPILED);
  }
