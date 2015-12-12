if (avctx->hwaccel
#if FF_API_CAP_VDPAU
                    || s->avctx->codec->capabilities&AV_CODEC_CAP_HWACCEL_VDPAU
#endif
                    )
                    buf_start_second_field = divider;
