#if defined(LITTLE_ENDIAN_ORDER) && !defined(FREESCALE_MMCAU)
if(!IS_INTEL_AVX1 && !IS_INTEL_AVX2)
            #endif
            ByteReverseWords(sha256->buffer, sha256->buffer, SHA256_BLOCK_SIZE);
