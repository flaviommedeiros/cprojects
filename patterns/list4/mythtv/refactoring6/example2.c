if(s->avctx->hwaccel && s->avctx->hwaccel->decode_slice           ||
#if FF_API_CAP_VDPAU
       s->avctx->codec->capabilities&AV_CODEC_CAP_HWACCEL_VDPAU          ||
#endif
       !s->cur_pic.f                                                  ||
       s->cur_pic.field_picture
    )
        return 0;
