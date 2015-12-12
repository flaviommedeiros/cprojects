static cmsFormatters16 OutputFormatters16[] = {
    //    Type                                          Mask                  Function
    //  ----------------------------   ------------------------------------  ----------------------------

    { TYPE_Lab_DBL,                                      ANYPLANAR|ANYEXTRA,  PackLabDoubleFrom16},
    { TYPE_XYZ_DBL,                                      ANYPLANAR|ANYEXTRA,  PackXYZDoubleFrom16},

    { TYPE_Lab_FLT,                                      ANYPLANAR|ANYEXTRA,  PackLabFloatFrom16},
    { TYPE_XYZ_FLT,                                      ANYPLANAR|ANYEXTRA,  PackXYZFloatFrom16},
    
    { FLOAT_SH(1)|BYTES_SH(0),      ANYFLAVOR|ANYSWAPFIRST|ANYSWAP|
                                    ANYCHANNELS|ANYPLANAR|ANYEXTRA|ANYSPACE,  PackDoubleFrom16},
    { FLOAT_SH(1)|BYTES_SH(4),      ANYFLAVOR|ANYSWAPFIRST|ANYSWAP|
                                    ANYCHANNELS|ANYPLANAR|ANYEXTRA|ANYSPACE,  PackFloatFrom16},
#ifndef CMS_NO_HALF_SUPPORT 
    { FLOAT_SH(1)|BYTES_SH(2),      ANYFLAVOR|ANYSWAPFIRST|ANYSWAP|
                                    ANYCHANNELS|ANYPLANAR|ANYEXTRA|ANYSPACE,  PackHalfFrom16},
#endif

    { CHANNELS_SH(1)|BYTES_SH(1),                                  ANYSPACE,  Pack1Byte},
    { CHANNELS_SH(1)|BYTES_SH(1)|EXTRA_SH(1),                      ANYSPACE,  Pack1ByteSkip1},
    { CHANNELS_SH(1)|BYTES_SH(1)|EXTRA_SH(1)|SWAPFIRST_SH(1),      ANYSPACE,  Pack1ByteSkip1SwapFirst},

    { CHANNELS_SH(1)|BYTES_SH(1)|FLAVOR_SH(1),                     ANYSPACE,  Pack1ByteReversed},

    { TYPE_LabV2_8,                                                       0,  PackLabV2_8 },
    { TYPE_ALabV2_8,                                                      0,  PackALabV2_8 },
    { TYPE_LabV2_16,                                                      0,  PackLabV2_16 },

    { CHANNELS_SH(3)|BYTES_SH(1)|OPTIMIZED_SH(1),                  ANYSPACE,  Pack3BytesOptimized},
    { CHANNELS_SH(3)|BYTES_SH(1)|EXTRA_SH(1)|OPTIMIZED_SH(1),      ANYSPACE,  Pack3BytesAndSkip1Optimized},
    { CHANNELS_SH(3)|BYTES_SH(1)|EXTRA_SH(1)|SWAPFIRST_SH(1)|OPTIMIZED_SH(1),
                                                                   ANYSPACE,  Pack3BytesAndSkip1SwapFirstOptimized},
    { CHANNELS_SH(3)|BYTES_SH(1)|EXTRA_SH(1)|DOSWAP_SH(1)|SWAPFIRST_SH(1)|OPTIMIZED_SH(1),
                                                                   ANYSPACE,  Pack3BytesAndSkip1SwapSwapFirstOptimized},
    { CHANNELS_SH(3)|BYTES_SH(1)|DOSWAP_SH(1)|EXTRA_SH(1)|OPTIMIZED_SH(1),
                                                                   ANYSPACE,  Pack3BytesAndSkip1SwapOptimized},
    { CHANNELS_SH(3)|BYTES_SH(1)|DOSWAP_SH(1)|OPTIMIZED_SH(1),     ANYSPACE,  Pack3BytesSwapOptimized},



    { CHANNELS_SH(3)|BYTES_SH(1),                                  ANYSPACE,  Pack3Bytes},
    { CHANNELS_SH(3)|BYTES_SH(1)|EXTRA_SH(1),                      ANYSPACE,  Pack3BytesAndSkip1},
    { CHANNELS_SH(3)|BYTES_SH(1)|EXTRA_SH(1)|SWAPFIRST_SH(1),      ANYSPACE,  Pack3BytesAndSkip1SwapFirst},
    { CHANNELS_SH(3)|BYTES_SH(1)|EXTRA_SH(1)|DOSWAP_SH(1)|SWAPFIRST_SH(1),
                                                                   ANYSPACE,  Pack3BytesAndSkip1SwapSwapFirst},
    { CHANNELS_SH(3)|BYTES_SH(1)|DOSWAP_SH(1)|EXTRA_SH(1),         ANYSPACE,  Pack3BytesAndSkip1Swap},
    { CHANNELS_SH(3)|BYTES_SH(1)|DOSWAP_SH(1),                     ANYSPACE,  Pack3BytesSwap},
    { CHANNELS_SH(6)|BYTES_SH(1),                                  ANYSPACE,  Pack6Bytes},
    { CHANNELS_SH(6)|BYTES_SH(1)|DOSWAP_SH(1),                     ANYSPACE,  Pack6BytesSwap},
    { CHANNELS_SH(4)|BYTES_SH(1),                                  ANYSPACE,  Pack4Bytes},
    { CHANNELS_SH(4)|BYTES_SH(1)|FLAVOR_SH(1),                     ANYSPACE,  Pack4BytesReverse},
    { CHANNELS_SH(4)|BYTES_SH(1)|SWAPFIRST_SH(1),                  ANYSPACE,  Pack4BytesSwapFirst},
    { CHANNELS_SH(4)|BYTES_SH(1)|DOSWAP_SH(1),                     ANYSPACE,  Pack4BytesSwap},
    { CHANNELS_SH(4)|BYTES_SH(1)|DOSWAP_SH(1)|SWAPFIRST_SH(1),     ANYSPACE,  Pack4BytesSwapSwapFirst},

    { BYTES_SH(1),                 ANYFLAVOR|ANYSWAPFIRST|ANYSWAP|ANYEXTRA|ANYCHANNELS|ANYSPACE, PackAnyBytes},
    { BYTES_SH(1)|PLANAR_SH(1),    ANYFLAVOR|ANYSWAPFIRST|ANYSWAP|ANYEXTRA|ANYCHANNELS|ANYSPACE, PackPlanarBytes},

    { CHANNELS_SH(1)|BYTES_SH(2),                                  ANYSPACE,  Pack1Word},
    { CHANNELS_SH(1)|BYTES_SH(2)|EXTRA_SH(1),                      ANYSPACE,  Pack1WordSkip1},
    { CHANNELS_SH(1)|BYTES_SH(2)|EXTRA_SH(1)|SWAPFIRST_SH(1),      ANYSPACE,  Pack1WordSkip1SwapFirst},
    { CHANNELS_SH(1)|BYTES_SH(2)|FLAVOR_SH(1),                     ANYSPACE,  Pack1WordReversed},
    { CHANNELS_SH(1)|BYTES_SH(2)|ENDIAN16_SH(1),                   ANYSPACE,  Pack1WordBigEndian},
    { CHANNELS_SH(3)|BYTES_SH(2),                                  ANYSPACE,  Pack3Words},
    { CHANNELS_SH(3)|BYTES_SH(2)|DOSWAP_SH(1),                     ANYSPACE,  Pack3WordsSwap},
    { CHANNELS_SH(3)|BYTES_SH(2)|ENDIAN16_SH(1),                   ANYSPACE,  Pack3WordsBigEndian},
    { CHANNELS_SH(3)|BYTES_SH(2)|EXTRA_SH(1),                      ANYSPACE,  Pack3WordsAndSkip1},
    { CHANNELS_SH(3)|BYTES_SH(2)|EXTRA_SH(1)|DOSWAP_SH(1),         ANYSPACE,  Pack3WordsAndSkip1Swap},
    { CHANNELS_SH(3)|BYTES_SH(2)|EXTRA_SH(1)|SWAPFIRST_SH(1),      ANYSPACE,  Pack3WordsAndSkip1SwapFirst},

    { CHANNELS_SH(3)|BYTES_SH(2)|EXTRA_SH(1)|DOSWAP_SH(1)|SWAPFIRST_SH(1),
                                                                   ANYSPACE,  Pack3WordsAndSkip1SwapSwapFirst},

    { CHANNELS_SH(4)|BYTES_SH(2),                                  ANYSPACE,  Pack4Words},
    { CHANNELS_SH(4)|BYTES_SH(2)|FLAVOR_SH(1),                     ANYSPACE,  Pack4WordsReverse},
    { CHANNELS_SH(4)|BYTES_SH(2)|DOSWAP_SH(1),                     ANYSPACE,  Pack4WordsSwap},
    { CHANNELS_SH(4)|BYTES_SH(2)|ENDIAN16_SH(1),                   ANYSPACE,  Pack4WordsBigEndian},

    { CHANNELS_SH(6)|BYTES_SH(2),                                  ANYSPACE,  Pack6Words},
    { CHANNELS_SH(6)|BYTES_SH(2)|DOSWAP_SH(1),                     ANYSPACE,  Pack6WordsSwap},

    { BYTES_SH(2)|PLANAR_SH(1),     ANYFLAVOR|ANYENDIAN|ANYSWAP|ANYEXTRA|ANYCHANNELS|ANYSPACE, PackPlanarWords},
    { BYTES_SH(2),                  ANYFLAVOR|ANYSWAPFIRST|ANYSWAP|ANYENDIAN|ANYEXTRA|ANYCHANNELS|ANYSPACE, PackAnyWords}

};
