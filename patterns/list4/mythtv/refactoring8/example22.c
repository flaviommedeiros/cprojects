static void permute(int16_t dst[64], const int16_t src[64],
                    enum idct_permutation_type perm_type)
{
    int i;

#if ARCH_X86
    if (permute_x86(dst, src, perm_type))
        return;
#endif

    switch (perm_type) {
    case FF_IDCT_PERM_LIBMPEG2:
        for (i = 0; i < 64; i++)
            dst[(i & 0x38) | ((i & 6) >> 1) | ((i & 1) << 2)] = src[i];
        break;
    case FF_IDCT_PERM_PARTTRANS:
        for (i = 0; i < 64; i++)
            dst[(i & 0x24) | ((i & 3) << 3) | ((i >> 3) & 3)] = src[i];
        break;
    case FF_IDCT_PERM_TRANSPOSE:
        for (i = 0; i < 64; i++)
            dst[(i>>3) | ((i<<3)&0x38)] = src[i];
        break;
    default:
        for (i = 0; i < 64; i++)
            dst[i] = src[i];
        break;
    }
}
