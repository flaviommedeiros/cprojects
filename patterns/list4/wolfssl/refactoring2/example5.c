#if defined(HAVE_INTEL_AVX1) || defined(HAVE_INTEL_AVX2)
if(IS_INTEL_AVX1 || IS_INTEL_AVX2)
        #endif
        ByteReverseWords(&sha256->buffer[SHA256_PAD_SIZE/sizeof(word32)],
                         &sha256->buffer[SHA256_PAD_SIZE/sizeof(word32)],
                         2 * sizeof(word32));
