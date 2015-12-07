#ifdef AU_OGGFLAC
if ((ctx->state.ogg = OggFLAC__stream_encoder_get_state(ctx->encoder.ogg.stream)) != OggFLAC__STREAM_ENCODER_OK) {
      ctl->cmsg(CMSG_ERROR, VERB_NORMAL, "OggFLAC stream encoder is invalid (%s)",
		OggFLAC__StreamEncoderStateString[ctx->state.ogg]);
      /* fall through */
    }
