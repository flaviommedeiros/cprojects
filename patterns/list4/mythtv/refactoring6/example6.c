if (avctx->hwaccel
#if FF_API_VDPAU
        || uses_vdpau(avctx)
#endif
        )
        if (avctx->idct_algo == FF_IDCT_AUTO)
            avctx->idct_algo = FF_IDCT_SIMPLE;
