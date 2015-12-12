if (enccfg.rc_end_usage == VPX_CQ
#if CONFIG_LIBVPX_VP9_ENCODER
        || enccfg.rc_end_usage == VPX_Q
#endif
       ) {
        if (ctx->crf < enccfg.rc_min_quantizer || ctx->crf > enccfg.rc_max_quantizer) {
            av_log(avctx, AV_LOG_ERROR,
                   "CQ level %d must be between minimum and maximum quantizer value (%d-%d)\n",
                   ctx->crf, enccfg.rc_min_quantizer, enccfg.rc_max_quantizer);
            return AVERROR(EINVAL);
        }
    }
