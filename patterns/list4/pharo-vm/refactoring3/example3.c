switch (pass_mode) {
  case JBUF_PASS_THRU:
    if (cinfo->quantize_colors) {
      /* Single-pass processing with color quantization. */
      post->pub.post_process_data = post_process_1pass;
      /* We could be doing buffered-image output before starting a 2-pass
       * color quantization; in that case, jinit_d_post_controller did not
       * allocate a strip buffer.  Use the virtual-array buffer as workspace.
       */
      if (post->buffer == NULL) {
	post->buffer = (*cinfo->mem->access_virt_sarray)
	  ((j_common_ptr) cinfo, post->whole_image,
	   (JDIMENSION) 0, post->strip_height, TRUE);
      }
    } else {
      /* For single-pass processing without color quantization,
       * I have no work to do; just call the upsampler directly.
       */
      post->pub.post_process_data = cinfo->upsample->upsample;
    }
    break;
#ifdef QUANT_2PASS_SUPPORTED
  case JBUF_SAVE_AND_PASS:
    /* First pass of 2-pass quantization */
    if (post->whole_image == NULL)
      ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    post->pub.post_process_data = post_process_prepass;
    break;
  case JBUF_CRANK_DEST:
    /* Second pass of 2-pass quantization */
    if (post->whole_image == NULL)
      ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    post->pub.post_process_data = post_process_2pass;
    break;
#endif /* QUANT_2PASS_SUPPORTED */
  default:
    ERREXIT(cinfo, JERR_BAD_BUFFER_MODE);
    break;
  }
