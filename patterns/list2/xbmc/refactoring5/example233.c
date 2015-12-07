#ifdef AU_OGGFLAC
if (flac_options.isogg) {
    if ((ctx->encoder.ogg.stream = OggFLAC__stream_encoder_new()) == NULL) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot create OggFLAC stream");
      flac_session_close();
      return -1;
    }

    OggFLAC__stream_encoder_set_channels(ctx->encoder.ogg.stream, nch);
    /* 16bps only */
    OggFLAC__stream_encoder_set_bits_per_sample(ctx->encoder.ogg.stream, 16);

    /* set sequential number for serial */
    serial_number++;
    if (serial_number == 1) {
      srand(time(NULL));
      serial_number = rand();
    }
    OggFLAC__stream_encoder_set_serial_number(ctx->encoder.ogg.stream, serial_number);

    OggFLAC__stream_encoder_set_verify(ctx->encoder.ogg.stream, flac_options.verify);

    if (!FLAC__format_sample_rate_is_valid(dpm.rate)) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "invalid sampling rate %d",
		dpm.rate);
      flac_session_close();
      return -1;
    }
    OggFLAC__stream_encoder_set_sample_rate(ctx->encoder.ogg.stream, dpm.rate);

    OggFLAC__stream_encoder_set_qlp_coeff_precision(ctx->encoder.ogg.stream, flac_options.qlp_coeff_precision);
    /* expensive! */
    OggFLAC__stream_encoder_set_do_qlp_coeff_prec_search(ctx->encoder.ogg.stream, flac_options.qlp_coeff_precision_search);

    if (nch == 2) {
      OggFLAC__stream_encoder_set_do_mid_side_stereo(ctx->encoder.ogg.stream, flac_options.mid_side);
      OggFLAC__stream_encoder_set_loose_mid_side_stereo(ctx->encoder.ogg.stream, flac_options.adaptive_mid_side);
    }

    OggFLAC__stream_encoder_set_max_lpc_order(ctx->encoder.ogg.stream, flac_options.max_lpc_order);
    OggFLAC__stream_encoder_set_min_residual_partition_order(ctx->encoder.ogg.stream, flac_options.min_residual_partition_order);
    OggFLAC__stream_encoder_set_max_residual_partition_order(ctx->encoder.ogg.stream, flac_options.max_residual_partition_order);

    OggFLAC__stream_encoder_set_blocksize(ctx->encoder.ogg.stream, flac_options.blocksize);

    OggFLAC__stream_encoder_set_client_data(ctx->encoder.ogg.stream, ctx);

    if (0 < num_metadata)
      OggFLAC__stream_encoder_set_metadata(ctx->encoder.ogg.stream, metadata, num_metadata);

    /* set callback */
    OggFLAC__stream_encoder_set_write_callback(ctx->encoder.ogg.stream, ogg_stream_encoder_write_callback);

    ctx->state.ogg = OggFLAC__stream_encoder_init(ctx->encoder.ogg.stream);
    if (ctx->state.ogg != OggFLAC__STREAM_ENCODER_OK) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot create OggFLAC state (%s)",
		OggFLAC__StreamEncoderStateString[ctx->state.ogg]);
      flac_session_close();
      return -1;
    }
  }
  else
#endif /* AU_OGGFLAC */
  if (flac_options.seekable) {
    if ((ctx->encoder.flac.s_stream = FLAC__seekable_stream_encoder_new()) == NULL) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot create FLAC stream");
      flac_session_close();
      return -1;
    }

    FLAC__seekable_stream_encoder_set_channels(ctx->encoder.flac.s_stream, nch);
    /* 16bps only */
    FLAC__seekable_stream_encoder_set_bits_per_sample(ctx->encoder.flac.s_stream, 16);

    FLAC__seekable_stream_encoder_set_verify(ctx->encoder.flac.s_stream, flac_options.verify);

    if (!FLAC__format_sample_rate_is_valid(dpm.rate)) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "invalid sampling rate %d",
		dpm.rate);
      flac_session_close();
      return -1;
    }
    FLAC__seekable_stream_encoder_set_sample_rate(ctx->encoder.flac.s_stream, dpm.rate);

    FLAC__seekable_stream_encoder_set_qlp_coeff_precision(ctx->encoder.flac.s_stream, flac_options.qlp_coeff_precision);
    /* expensive! */
    FLAC__seekable_stream_encoder_set_do_qlp_coeff_prec_search(ctx->encoder.flac.s_stream, flac_options.qlp_coeff_precision_search);

    if (nch == 2) {
      FLAC__seekable_stream_encoder_set_do_mid_side_stereo(ctx->encoder.flac.s_stream, flac_options.mid_side);
      FLAC__seekable_stream_encoder_set_loose_mid_side_stereo(ctx->encoder.flac.s_stream, flac_options.adaptive_mid_side);
    }

    FLAC__seekable_stream_encoder_set_max_lpc_order(ctx->encoder.flac.s_stream, flac_options.max_lpc_order);
    FLAC__seekable_stream_encoder_set_min_residual_partition_order(ctx->encoder.flac.s_stream, flac_options.min_residual_partition_order);
    FLAC__seekable_stream_encoder_set_max_residual_partition_order(ctx->encoder.flac.s_stream, flac_options.max_residual_partition_order);

    FLAC__seekable_stream_encoder_set_blocksize(ctx->encoder.flac.s_stream, flac_options.blocksize);
    FLAC__seekable_stream_encoder_set_client_data(ctx->encoder.flac.s_stream, ctx);

    if (0 < num_metadata)
      FLAC__seekable_stream_encoder_set_metadata(ctx->encoder.flac.s_stream, metadata, num_metadata);

    /* set callback */
/*    FLAC__seekable_stream_encoder_set_metadata_callback(ctx->encoder.flac.s_stream, flac_seekable_stream_encoder_metadata_callback); /* */
#ifndef __BORLANDC__
    FLAC__stream_encoder_set_metadata_callback(ctx->encoder.flac.s_stream, flac_seekable_stream_encoder_metadata_callback); /* */
#endif
    FLAC__seekable_stream_encoder_set_write_callback(ctx->encoder.flac.s_stream, flac_seekable_stream_encoder_write_callback);

    ctx->state.s_flac = FLAC__seekable_stream_encoder_init(ctx->encoder.flac.s_stream);
    if (ctx->state.s_flac != FLAC__SEEKABLE_STREAM_ENCODER_OK) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot create FLAC state (%s)",
		FLAC__SeekableStreamEncoderStateString[ctx->state.s_flac]);
      flac_session_close();
      return -1;
    }
	}
	else
  {
    if ((ctx->encoder.flac.stream = FLAC__stream_encoder_new()) == NULL) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot create FLAC stream");
      flac_session_close();
      return -1;
    }

    FLAC__stream_encoder_set_channels(ctx->encoder.flac.stream, nch);
    /* 16bps only */
    FLAC__stream_encoder_set_bits_per_sample(ctx->encoder.flac.stream, 16);

    FLAC__stream_encoder_set_verify(ctx->encoder.flac.stream, flac_options.verify);

    if (!FLAC__format_sample_rate_is_valid(dpm.rate)) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "invalid sampling rate %d",
		dpm.rate);
      flac_session_close();
      return -1;
    }
    FLAC__stream_encoder_set_sample_rate(ctx->encoder.flac.stream, dpm.rate);

    FLAC__stream_encoder_set_qlp_coeff_precision(ctx->encoder.flac.stream, flac_options.qlp_coeff_precision);
    /* expensive! */
    FLAC__stream_encoder_set_do_qlp_coeff_prec_search(ctx->encoder.flac.stream, flac_options.qlp_coeff_precision_search);

    if (nch == 2) {
      FLAC__stream_encoder_set_do_mid_side_stereo(ctx->encoder.flac.stream, flac_options.mid_side);
      FLAC__stream_encoder_set_loose_mid_side_stereo(ctx->encoder.flac.stream, flac_options.adaptive_mid_side);
    }

    FLAC__stream_encoder_set_max_lpc_order(ctx->encoder.flac.stream, flac_options.max_lpc_order);
    FLAC__stream_encoder_set_min_residual_partition_order(ctx->encoder.flac.stream, flac_options.min_residual_partition_order);
    FLAC__stream_encoder_set_max_residual_partition_order(ctx->encoder.flac.stream, flac_options.max_residual_partition_order);

    FLAC__stream_encoder_set_blocksize(ctx->encoder.flac.stream, flac_options.blocksize);
    FLAC__stream_encoder_set_client_data(ctx->encoder.flac.stream, ctx);

    if (0 < num_metadata)
      FLAC__stream_encoder_set_metadata(ctx->encoder.flac.stream, metadata, num_metadata);

    /* set callback */
    FLAC__stream_encoder_set_metadata_callback(ctx->encoder.flac.stream, flac_stream_encoder_metadata_callback);
    FLAC__stream_encoder_set_write_callback(ctx->encoder.flac.stream, flac_stream_encoder_write_callback);

    ctx->state.flac = FLAC__stream_encoder_init(ctx->encoder.flac.stream);
    if (ctx->state.flac != FLAC__STREAM_ENCODER_OK) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "cannot create FLAC state (%s)",
		FLAC__StreamEncoderStateString[ctx->state.flac]);
      flac_session_close();
      return -1;
    }
  }
