switch (avctx->profile & ~FF_PROFILE_H264_INTRA) {
        case FF_PROFILE_H264_BASELINE:         PROFILE(H264_BASELINE);
        case FF_PROFILE_H264_CONSTRAINED_BASELINE:
        case FF_PROFILE_H264_MAIN:             PROFILE(H264_MAIN);
        case FF_PROFILE_H264_HIGH:             PROFILE(H264_HIGH);
#ifdef VDP_DECODER_PROFILE_H264_EXTENDED
        case FF_PROFILE_H264_EXTENDED:         PROFILE(H264_EXTENDED);
#endif
        default:                               return AVERROR(EINVAL);
        }
