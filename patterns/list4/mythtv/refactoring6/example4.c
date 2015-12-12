if(!h->frame_recovered && !h->avctx->hwaccel
#if FF_API_CAP_VDPAU
       && !(h->avctx->codec->capabilities & AV_CODEC_CAP_HWACCEL_VDPAU)
#endif
       )
        avpriv_color_frame(pic->f, c);
