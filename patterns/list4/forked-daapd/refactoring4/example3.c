#if LIBAVCODEC_VERSION_MAJOR >= 55 || (LIBAVCODEC_VERSION_MAJOR == 54 && LIBAVCODEC_VERSION_MINOR >= 35)
if (audio_codec_id == AV_CODEC_ID_NONE)
#else
  if (audio_codec_id == CODEC_ID_NONE)
#endif
    {
      DPRINTF(E_DBG, L_SCAN, "File has no audio streams, discarding\n");

#if LIBAVFORMAT_VERSION_MAJOR >= 54 || (LIBAVFORMAT_VERSION_MAJOR == 53 && LIBAVFORMAT_VERSION_MINOR >= 21)
      avformat_close_input(&ctx);
#else
      av_close_input_file(ctx);
#endif
      return -1;
    }
