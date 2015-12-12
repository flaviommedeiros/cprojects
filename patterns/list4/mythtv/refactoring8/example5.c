int ff_get_format(AVCodecContext *avctx, const enum AVPixelFormat *fmt)
{
    const AVPixFmtDescriptor *desc;
    enum AVPixelFormat *choices;
    enum AVPixelFormat ret;
    unsigned n = 0;

    while (fmt[n] != AV_PIX_FMT_NONE)
        ++n;

    av_assert0(n >= 1);
    avctx->sw_pix_fmt = fmt[n - 1];
    av_assert2(!is_hwaccel_pix_fmt(avctx->sw_pix_fmt));

    choices = av_malloc_array(n + 1, sizeof(*choices));
    if (!choices)
        return AV_PIX_FMT_NONE;

    memcpy(choices, fmt, (n + 1) * sizeof(*choices));

    for (;;) {
        if (avctx->hwaccel && avctx->hwaccel->uninit)
            avctx->hwaccel->uninit(avctx);
        av_freep(&avctx->internal->hwaccel_priv_data);
        avctx->hwaccel = NULL;

        ret = avctx->get_format(avctx, choices);

        desc = av_pix_fmt_desc_get(ret);
        if (!desc) {
            ret = AV_PIX_FMT_NONE;
            break;
        }

        if (!(desc->flags & AV_PIX_FMT_FLAG_HWACCEL))
            break;
#if FF_API_CAP_VDPAU
        if (avctx->codec->capabilities&AV_CODEC_CAP_HWACCEL_VDPAU)
            break;
#endif

        if (!setup_hwaccel(avctx, ret, desc->name))
            break;

        /* Remove failed hwaccel from choices */
        for (n = 0; choices[n] != ret; n++)
            av_assert0(choices[n] != AV_PIX_FMT_NONE);

        do
            choices[n] = choices[n + 1];
        while (choices[n++] != AV_PIX_FMT_NONE);
    }

    av_freep(&choices);
    return ret;
}
