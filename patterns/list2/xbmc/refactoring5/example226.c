#ifdef HAVE_NASM
if (gfc->CPU_features.AMD_3DNow) {
        gfc->fft_fht = fht_3DN;
    }
    else if (gfc->CPU_features.SSE) {
        gfc->fft_fht = fht_SSE;
    }
    else
#endif
    {
        gfc->fft_fht = fht;
    }
