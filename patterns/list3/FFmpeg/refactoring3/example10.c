switch (avctx->profile & ~FF_PROFILE_H264_INTRA) {
    case FF_PROFILE_H264_BASELINE:
        profile = VDP_DECODER_PROFILE_H264_BASELINE;
        break;
    case FF_PROFILE_H264_CONSTRAINED_BASELINE:
#ifdef VDP_DECODER_PROFILE_H264_CONSTRAINED_BASELINE
        profile = VDP_DECODER_PROFILE_H264_CONSTRAINED_BASELINE;
        break;
#endif
    case FF_PROFILE_H264_MAIN:
        profile = VDP_DECODER_PROFILE_H264_MAIN;
        break;
    case FF_PROFILE_H264_HIGH:
        profile = VDP_DECODER_PROFILE_H264_HIGH;
        break;
#ifdef VDP_DECODER_PROFILE_H264_EXTENDED
    case FF_PROFILE_H264_EXTENDED:
        profile = VDP_DECODER_PROFILE_H264_EXTENDED;
        break;
#endif
    case FF_PROFILE_H264_HIGH_10:
        /* XXX: High 10 can be treated as High so long as only 8-bits per
         * formats are supported. */
        profile = VDP_DECODER_PROFILE_H264_HIGH;
        break;
#ifdef VDP_DECODER_PROFILE_H264_HIGH_444_PREDICTIVE
    case FF_PROFILE_H264_HIGH_422:
    case FF_PROFILE_H264_HIGH_444_PREDICTIVE:
    case FF_PROFILE_H264_CAVLC_444:
        profile = VDP_DECODER_PROFILE_H264_HIGH_444_PREDICTIVE;
        break;
#endif
    default:
        return AVERROR(ENOTSUP);
    }
