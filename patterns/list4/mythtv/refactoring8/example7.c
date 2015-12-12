av_cold int ff_rdft_init(RDFTContext *s, int nbits, enum RDFTransformType trans)
{
    int n = 1 << nbits;
    int ret;

    s->nbits           = nbits;
    s->inverse         = trans == IDFT_C2R || trans == DFT_C2R;
    s->sign_convention = trans == IDFT_R2C || trans == DFT_C2R ? 1 : -1;

    if (nbits < 4 || nbits > 16)
        return AVERROR(EINVAL);

    if ((ret = ff_fft_init(&s->fft, nbits-1, trans == IDFT_C2R || trans == IDFT_R2C)) < 0)
        return ret;

    ff_init_ff_cos_tabs(nbits);
    s->tcos = ff_cos_tabs[nbits];
    s->tsin = ff_sin_tabs[nbits]+(trans == DFT_R2C || trans == DFT_C2R)*(n>>2);
#if !CONFIG_HARDCODED_TABLES
    {
        int i;
        const double theta = (trans == DFT_R2C || trans == DFT_C2R ? -1 : 1) * 2 * M_PI / n;
        for (i = 0; i < (n >> 2); i++)
            s->tsin[i] = sin(i * theta);
    }
#endif
    s->rdft_calc   = rdft_calc_c;

    if (ARCH_ARM) ff_rdft_init_arm(s);

    return 0;
}
