if (ctx->codec_type ==
#if LIBAVCODEC_VERSION_INT >= AV_VERSION_INT(52, 64, 0)
            AVMEDIA_TYPE_AUDIO)
#else
            CODEC_TYPE_AUDIO
