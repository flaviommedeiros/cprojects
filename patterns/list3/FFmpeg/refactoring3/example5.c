switch (img->fmt) {
    case VPX_IMG_FMT_I420:
        if (avctx->codec_id == AV_CODEC_ID_VP9)
            avctx->profile = FF_PROFILE_VP9_0;
        avctx->pix_fmt = AV_PIX_FMT_YUV420P;
        return 0;
#if CONFIG_LIBVPX_VP9_DECODER
    case VPX_IMG_FMT_I422:
        avctx->profile = FF_PROFILE_VP9_1;
        avctx->pix_fmt = AV_PIX_FMT_YUV422P;
        return 0;
#if VPX_IMAGE_ABI_VERSION >= 3
    case VPX_IMG_FMT_I440:
        avctx->profile = FF_PROFILE_VP9_1;
        avctx->pix_fmt = AV_PIX_FMT_YUV440P;
        return 0;
#endif
    case VPX_IMG_FMT_I444:
        avctx->profile = FF_PROFILE_VP9_1;
#if VPX_IMAGE_ABI_VERSION >= 3
        avctx->pix_fmt = avctx->colorspace == AVCOL_SPC_RGB ?
                         AV_PIX_FMT_GBRP : AV_PIX_FMT_YUV444P;
#else
        avctx->pix_fmt = AV_PIX_FMT_YUV444P;
#endif
        return 0;
#ifdef VPX_IMG_FMT_HIGHBITDEPTH
    case VPX_IMG_FMT_I42016:
        avctx->profile = FF_PROFILE_VP9_2;
        if (img->bit_depth == 10) {
            avctx->pix_fmt = AV_PIX_FMT_YUV420P10LE;
            return 0;
        } else if (img->bit_depth == 12) {
            avctx->pix_fmt = AV_PIX_FMT_YUV420P12LE;
            return 0;
        } else {
            return AVERROR_INVALIDDATA;
        }
    case VPX_IMG_FMT_I42216:
        avctx->profile = FF_PROFILE_VP9_3;
        if (img->bit_depth == 10) {
            avctx->pix_fmt = AV_PIX_FMT_YUV422P10LE;
            return 0;
        } else if (img->bit_depth == 12) {
            avctx->pix_fmt = AV_PIX_FMT_YUV422P12LE;
            return 0;
        } else {
            return AVERROR_INVALIDDATA;
        }
#if VPX_IMAGE_ABI_VERSION >= 3
    case VPX_IMG_FMT_I44016:
        avctx->profile = FF_PROFILE_VP9_3;
        if (img->bit_depth == 10) {
            avctx->pix_fmt = AV_PIX_FMT_YUV440P10LE;
            return 0;
        } else if (img->bit_depth == 12) {
            avctx->pix_fmt = AV_PIX_FMT_YUV440P12LE;
            return 0;
        } else {
            return AVERROR_INVALIDDATA;
        }
#endif
    case VPX_IMG_FMT_I44416:
        avctx->profile = FF_PROFILE_VP9_3;
        if (img->bit_depth == 10) {
#if VPX_IMAGE_ABI_VERSION >= 3
            avctx->pix_fmt = avctx->colorspace == AVCOL_SPC_RGB ?
                             AV_PIX_FMT_GBRP10LE : AV_PIX_FMT_YUV444P10LE;
#else
            avctx->pix_fmt = AV_PIX_FMT_YUV444P10LE;
#endif
            return 0;
        } else if (img->bit_depth == 12) {
#if VPX_IMAGE_ABI_VERSION >= 3
            avctx->pix_fmt = avctx->colorspace == AVCOL_SPC_RGB ?
                             AV_PIX_FMT_GBRP12LE : AV_PIX_FMT_YUV444P12LE;
#else
            avctx->pix_fmt = AV_PIX_FMT_YUV444P12LE;
#endif
            return 0;
        } else {
            return AVERROR_INVALIDDATA;
        }
#endif
#endif
    default:
        return AVERROR_INVALIDDATA;
    }
