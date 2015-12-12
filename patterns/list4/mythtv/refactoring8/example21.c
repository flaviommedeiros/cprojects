static const struct algo fdct_tab[] = {
    { "REF-DBL",     ff_ref_fdct,          FF_IDCT_PERM_NONE },
    { "IJG-AAN-INT", ff_fdct_ifast,        FF_IDCT_PERM_NONE },
    { "IJG-LLM-INT", ff_jpeg_fdct_islow_8, FF_IDCT_PERM_NONE },
#if CONFIG_FAANDCT
    { "FAAN",        ff_faandct,           FF_IDCT_PERM_NONE },
#endif /* CONFIG_FAANDCT */
};
