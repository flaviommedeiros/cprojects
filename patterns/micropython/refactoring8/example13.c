static const FPTYPE g_neg_pow[] = {
    #if FPDECEXP > 32
    1e-256, 1e-128, 1e-64,
    #endif
    1e-32, 1e-16, 1e-8, 1e-4, 1e-2, 1e-1
};
