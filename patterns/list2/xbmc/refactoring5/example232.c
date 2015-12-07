#ifdef AU_OGGFLAC
if (flac_options.isogg) {
      if (ctx->encoder.ogg.stream) {
	OggFLAC__stream_encoder_finish(ctx->encoder.ogg.stream);
	OggFLAC__stream_encoder_delete(ctx->encoder.ogg.stream);
      }
    }
    else
#endif /* AU_OGGFLAC */
    if (flac_options.seekable) {
      if (ctx->encoder.flac.s_stream) {
	FLAC__seekable_stream_encoder_finish(ctx->encoder.flac.s_stream);
	FLAC__seekable_stream_encoder_delete(ctx->encoder.flac.s_stream);
      }
    }
    else
    {
      if (ctx->encoder.flac.stream) {
	FLAC__stream_encoder_finish(ctx->encoder.flac.stream);
	FLAC__stream_encoder_delete(ctx->encoder.flac.stream);
      }
    }
