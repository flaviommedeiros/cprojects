switch (avctx->pix_fmt) {
    case AV_PIX_FMT_YUV420P:
        enccfg->g_profile = 0;
        *img_fmt = VPX_IMG_FMT_I420;
        return 0;
    case AV_PIX_FMT_YUV422P:
        enccfg->g_profile = 1;
        *img_fmt = VPX_IMG_FMT_I422;
        return 0;
#if VPX_IMAGE_ABI_VERSION >= 3
    case AV_PIX_FMT_YUV440P:
        enccfg->g_profile = 1;
        *img_fmt = VPX_IMG_FMT_I440;
        return 0;
#endif
    case AV_PIX_FMT_YUV444P:
        enccfg->g_profile = 1;
        *img_fmt = VPX_IMG_FMT_I444;
        return 0;
#ifdef VPX_IMG_FMT_HIGHBITDEPTH
    case AV_PIX_FMT_YUV420P10LE:
    case AV_PIX_FMT_YUV420P12LE:
        if (codec_caps & VPX_CODEC_CAP_HIGHBITDEPTH) {
            enccfg->g_bit_depth = enccfg->g_input_bit_depth =
                avctx->pix_fmt == AV_PIX_FMT_YUV420P10LE ? 10 : 12;
            enccfg->g_profile = 2;
            *img_fmt = VPX_IMG_FMT_I42016;
            *flags |= VPX_CODEC_USE_HIGHBITDEPTH;
            return 0;
        }
        break;
    case AV_PIX_FMT_YUV422P10LE:
    case AV_PIX_FMT_YUV422P12LE:
        if (codec_caps & VPX_CODEC_CAP_HIGHBITDEPTH) {
            enccfg->g_bit_depth = enccfg->g_input_bit_depth =
                avctx->pix_fmt == AV_PIX_FMT_YUV422P10LE ? 10 : 12;
            enccfg->g_profile = 3;
            *img_fmt = VPX_IMG_FMT_I42216;
            *flags |= VPX_CODEC_USE_HIGHBITDEPTH;
            return 0;
        }
        break;
#if VPX_IMAGE_ABI_VERSION >= 3
    case AV_PIX_FMT_YUV440P10LE:
    case AV_PIX_FMT_YUV440P12LE:
        if (codec_caps & VPX_CODEC_CAP_HIGHBITDEPTH) {
            enccfg->g_bit_depth = enccfg->g_input_bit_depth =
                avctx->pix_fmt == AV_PIX_FMT_YUV440P10LE ? 10 : 12;
            enccfg->g_profile = 3;
            *img_fmt = VPX_IMG_FMT_I44016;
            *flags |= VPX_CODEC_USE_HIGHBITDEPTH;
            return 0;
        }
        break;
#endif
    case AV_PIX_FMT_YUV444P10LE:
    case AV_PIX_FMT_YUV444P12LE:
        if (codec_caps & VPX_CODEC_CAP_HIGHBITDEPTH) {
            enccfg->g_bit_depth = enccfg->g_input_bit_depth =
                avctx->pix_fmt == AV_PIX_FMT_YUV444P10LE ? 10 : 12;
            enccfg->g_profile = 3;
            *img_fmt = VPX_IMG_FMT_I44416;
            *flags |= VPX_CODEC_USE_HIGHBITDEPTH;
            return 0;
        }
        break;
#endif
    default:
        break;
    }
