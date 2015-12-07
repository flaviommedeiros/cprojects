#ifdef AU_OGGFLAC
if (flac_options.isogg) {
    ctx->state.ogg = OggFLAC__stream_encoder_get_state(ctx->encoder.ogg.stream);
    if (ctx->state.ogg != OggFLAC__STREAM_ENCODER_OK) {
      if (ctx->state.ogg == OggFLAC__STREAM_ENCODER_FLAC_STREAM_ENCODER_ERROR) {
	ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "FLAC stream verify error (%s)",
		  FLAC__StreamDecoderStateString[OggFLAC__stream_encoder_get_verify_decoder_state(ctx->encoder.ogg.stream)]);
      }
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot encode OggFLAC stream (%s)",
		OggFLAC__StreamEncoderStateString[ctx->state.ogg]);
      flac_session_close();
      return -1;
    }

    if (!OggFLAC__stream_encoder_process_interleaved(ctx->encoder.ogg.stream, oggbuf,
						     nbytes / nch / 2)) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot encode OggFLAC stream");
      flac_session_close();
      return -1;
    }
  }
  else
#endif /* AU_OGGFLAC */
	if (flac_options.seekable) {
    ctx->state.s_flac = FLAC__seekable_stream_encoder_get_state(ctx->encoder.flac.s_stream);
    if (ctx->state.s_flac != FLAC__STREAM_ENCODER_OK) {
      if (ctx->state.s_flac == FLAC__STREAM_ENCODER_VERIFY_DECODER_ERROR |
	  FLAC__STREAM_ENCODER_VERIFY_MISMATCH_IN_AUDIO_DATA) {
	ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "FLAC stream verify error (%s)",
		  FLAC__SeekableStreamDecoderStateString[FLAC__seekable_stream_encoder_get_verify_decoder_state(ctx->encoder.flac.s_stream)]);
      }
      else {
	ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot encode FLAC stream (%s)",
		  FLAC__SeekableStreamEncoderStateString[ctx->state.s_flac]);
      }
      flac_session_close();
      return -1;
    }

    if (!FLAC__seekable_stream_encoder_process_interleaved(ctx->encoder.flac.s_stream, oggbuf,
						  nbytes / nch / 2 )) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot encode FLAC stream");
      flac_session_close();
      return -1;
    }
	}
  else
	{
    ctx->state.flac = FLAC__stream_encoder_get_state(ctx->encoder.flac.stream);
    if (ctx->state.flac != FLAC__STREAM_ENCODER_OK) {
      if (ctx->state.flac == FLAC__STREAM_ENCODER_VERIFY_DECODER_ERROR |
	  FLAC__STREAM_ENCODER_VERIFY_MISMATCH_IN_AUDIO_DATA) {
	ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "FLAC stream verify error (%s)",
		  FLAC__StreamDecoderStateString[FLAC__stream_encoder_get_verify_decoder_state(ctx->encoder.flac.stream)]);
      }
      else {
	ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot encode FLAC stream (%s)",
		  FLAC__StreamEncoderStateString[ctx->state.flac]);
      }
      flac_session_close();
      return -1;
    }

    if (!FLAC__stream_encoder_process_interleaved(ctx->encoder.flac.stream, oggbuf,
						  nbytes / nch / 2 )) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot encode FLAC stream");
      flac_session_close();
      return -1;
    }
  }
