#if defined(LITTLE_ENDIAN_ORDER)
if(!IS_INTEL_AVX1 && !IS_INTEL_AVX2) 
            #endif
                 ByteReverseWords64(sha384->buffer, sha384->buffer,
                               SHA384_BLOCK_SIZE);
