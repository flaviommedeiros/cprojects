#ifdef HAVE_NASM
if (gfc->CPU_features.AMD_3DNow) {
            fft_asm_used = 1;
        }
        else if (gfc->CPU_features.SSE) {
            fft_asm_used = 2;
        }
        else
#endif
        {
            fft_asm_used = 0;
        }
