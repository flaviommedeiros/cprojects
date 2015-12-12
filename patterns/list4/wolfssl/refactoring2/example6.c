#if defined(LITTLE_ENDIAN_ORDER)
if(!IS_INTEL_AVX1 && !IS_INTEL_AVX2) 
                #endif
                    ByteReverseWords64(sha512->buffer, sha512->buffer,
                                   SHA512_BLOCK_SIZE);
