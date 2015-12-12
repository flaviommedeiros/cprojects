static cmsFormatters16 InputFormatters16[] = {

    //    Type                                          Mask                  Function
    //  ----------------------------   ------------------------------------  ----------------------------
    { TYPE_Lab_DBL,                                 ANYPLANAR|ANYEXTRA,   UnrollLabDoubleTo16},
    { TYPE_XYZ_DBL,                                 ANYPLANAR|ANYEXTRA,   UnrollXYZDoubleTo16},
    { TYPE_Lab_FLT,                                 ANYPLANAR|ANYEXTRA,   UnrollLabFloatTo16},
    { TYPE_XYZ_FLT,                                 ANYPLANAR|ANYEXTRA,   UnrollXYZFloatTo16},
    { TYPE_GRAY_DBL,                                                 0,   UnrollDouble1Chan},
    { FLOAT_SH(1)|BYTES_SH(0), ANYCHANNELS|ANYPLANAR|ANYSWAPFIRST|ANYFLAVOR|
                                             ANYSWAP|ANYEXTRA|ANYSPACE,   UnrollDoubleTo16},
    { FLOAT_SH(1)|BYTES_SH(4), ANYCHANNELS|ANYPLANAR|ANYSWAPFIRST|ANYFLAVOR|
                                             ANYSWAP|ANYEXTRA|ANYSPACE,   UnrollFloatTo16},
#ifndef CMS_NO_HALF_SUPPORT 
    { FLOAT_SH(1)|BYTES_SH(2), ANYCHANNELS|ANYPLANAR|ANYSWAPFIRST|ANYFLAVOR|
                                            ANYEXTRA|ANYSWAP|ANYSPACE,   UnrollHalfTo16},
#endif

    { CHANNELS_SH(1)|BYTES_SH(1),                              ANYSPACE,  Unroll1Byte},
    { CHANNELS_SH(1)|BYTES_SH(1)|EXTRA_SH(1),                  ANYSPACE,  Unroll1ByteSkip1},
    { CHANNELS_SH(1)|BYTES_SH(1)|EXTRA_SH(2),                  ANYSPACE,  Unroll1ByteSkip2},
    { CHANNELS_SH(1)|BYTES_SH(1)|FLAVOR_SH(1),                 ANYSPACE,  Unroll1ByteReversed},
    { COLORSPACE_SH(PT_MCH2)|CHANNELS_SH(2)|BYTES_SH(1),              0,  Unroll2Bytes},

    { TYPE_LabV2_8,                                                   0,  UnrollLabV2_8 },
    { TYPE_ALabV2_8,                                                  0,  UnrollALabV2_8 },
    { TYPE_LabV2_16,                                                  0,  UnrollLabV2_16 },

    { CHANNELS_SH(3)|BYTES_SH(1),                              ANYSPACE,  Unroll3Bytes},
    { CHANNELS_SH(3)|BYTES_SH(1)|DOSWAP_SH(1),                 ANYSPACE,  Unroll3BytesSwap},
    { CHANNELS_SH(3)|EXTRA_SH(1)|BYTES_SH(1)|DOSWAP_SH(1),     ANYSPACE,  Unroll3BytesSkip1Swap},
    { CHANNELS_SH(3)|EXTRA_SH(1)|BYTES_SH(1)|SWAPFIRST_SH(1),  ANYSPACE,  Unroll3BytesSkip1SwapFirst},

    { CHANNELS_SH(3)|EXTRA_SH(1)|BYTES_SH(1)|DOSWAP_SH(1)|SWAPFIRST_SH(1),  
                                                               ANYSPACE,  Unroll3BytesSkip1SwapSwapFirst},

    { CHANNELS_SH(4)|BYTES_SH(1),                              ANYSPACE,  Unroll4Bytes},
    { CHANNELS_SH(4)|BYTES_SH(1)|FLAVOR_SH(1),                 ANYSPACE,  Unroll4BytesReverse},
    { CHANNELS_SH(4)|BYTES_SH(1)|SWAPFIRST_SH(1),              ANYSPACE,  Unroll4BytesSwapFirst},
    { CHANNELS_SH(4)|BYTES_SH(1)|DOSWAP_SH(1),                 ANYSPACE,  Unroll4BytesSwap},
    { CHANNELS_SH(4)|BYTES_SH(1)|DOSWAP_SH(1)|SWAPFIRST_SH(1), ANYSPACE,  Unroll4BytesSwapSwapFirst},

    { BYTES_SH(1)|PLANAR_SH(1), ANYFLAVOR|ANYSWAPFIRST|
                                   ANYSWAP|ANYEXTRA|ANYCHANNELS|ANYSPACE, UnrollPlanarBytes},

    { BYTES_SH(1),    ANYFLAVOR|ANYSWAPFIRST|ANYSWAP|
                                           ANYEXTRA|ANYCHANNELS|ANYSPACE, UnrollChunkyBytes},

    { CHANNELS_SH(1)|BYTES_SH(2),                              ANYSPACE,  Unroll1Word},
    { CHANNELS_SH(1)|BYTES_SH(2)|FLAVOR_SH(1),                 ANYSPACE,  Unroll1WordReversed},
    { CHANNELS_SH(1)|BYTES_SH(2)|EXTRA_SH(3),                  ANYSPACE,  Unroll1WordSkip3},

    { CHANNELS_SH(2)|BYTES_SH(2),                              ANYSPACE,  Unroll2Words},
    { CHANNELS_SH(3)|BYTES_SH(2),                              ANYSPACE,  Unroll3Words},
    { CHANNELS_SH(4)|BYTES_SH(2),                              ANYSPACE,  Unroll4Words},

    { CHANNELS_SH(3)|BYTES_SH(2)|DOSWAP_SH(1),                 ANYSPACE,  Unroll3WordsSwap},
    { CHANNELS_SH(3)|BYTES_SH(2)|EXTRA_SH(1)|SWAPFIRST_SH(1),  ANYSPACE,  Unroll3WordsSkip1SwapFirst},
    { CHANNELS_SH(3)|BYTES_SH(2)|EXTRA_SH(1)|DOSWAP_SH(1),     ANYSPACE,  Unroll3WordsSkip1Swap},
    { CHANNELS_SH(4)|BYTES_SH(2)|FLAVOR_SH(1),                 ANYSPACE,  Unroll4WordsReverse},
    { CHANNELS_SH(4)|BYTES_SH(2)|SWAPFIRST_SH(1),              ANYSPACE,  Unroll4WordsSwapFirst},
    { CHANNELS_SH(4)|BYTES_SH(2)|DOSWAP_SH(1),                 ANYSPACE,  Unroll4WordsSwap},
    { CHANNELS_SH(4)|BYTES_SH(2)|DOSWAP_SH(1)|SWAPFIRST_SH(1), ANYSPACE,  Unroll4WordsSwapSwapFirst},


    { BYTES_SH(2)|PLANAR_SH(1),  ANYFLAVOR|ANYSWAP|ANYENDIAN|ANYEXTRA|ANYCHANNELS|ANYSPACE,  UnrollPlanarWords},
    { BYTES_SH(2),  ANYFLAVOR|ANYSWAPFIRST|ANYSWAP|ANYENDIAN|ANYEXTRA|ANYCHANNELS|ANYSPACE,  UnrollAnyWords},
};
