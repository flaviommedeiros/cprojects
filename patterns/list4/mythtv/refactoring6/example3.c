if (avctx->hwaccel
#if FF_API_CAP_VDPAU
        || avctx->codec->capabilities & AV_CODEC_CAP_HWACCEL_VDPAU
#endif
        )
        return 0;
