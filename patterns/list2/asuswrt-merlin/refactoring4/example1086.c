#if BENCHMARK_LIBLZO_SAFE
if (lzo1x_decompress_safe(comp, inlen, decomp, &outlen, NULL))
#elif BENCHMARK_LIBLZO_UNSAFE
        if (lzo1x_decompress(comp, inlen, decomp, &outlen, NULL))
#else
        if (av_lzo1x_decode(decomp, &outlen, comp, &inlen))
#endif
            av_log(NULL, AV_LOG_ERROR, "decompression error\n");
