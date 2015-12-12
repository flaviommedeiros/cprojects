static cmsFormattersFloat OutputFormattersFloat[] = {
    //    Type                                          Mask                                 Function
    //  ----------------------------   ---------------------------------------------------  ----------------------------
    {     TYPE_Lab_FLT,                                                ANYPLANAR|ANYEXTRA,   PackLabFloatFromFloat},
    {     TYPE_XYZ_FLT,                                                ANYPLANAR|ANYEXTRA,   PackXYZFloatFromFloat},

    {     TYPE_Lab_DBL,                                                ANYPLANAR|ANYEXTRA,   PackLabDoubleFromFloat},
    {     TYPE_XYZ_DBL,                                                ANYPLANAR|ANYEXTRA,   PackXYZDoubleFromFloat},

    {     FLOAT_SH(1)|BYTES_SH(4), ANYPLANAR|
                             ANYFLAVOR|ANYSWAPFIRST|ANYSWAP|ANYEXTRA|ANYCHANNELS|ANYSPACE,   PackFloatsFromFloat },
    {     FLOAT_SH(1)|BYTES_SH(0), ANYPLANAR|
                             ANYFLAVOR|ANYSWAPFIRST|ANYSWAP|ANYEXTRA|ANYCHANNELS|ANYSPACE,   PackDoublesFromFloat },
#ifndef CMS_NO_HALF_SUPPORT 
    {     FLOAT_SH(1)|BYTES_SH(2),                                   
                             ANYFLAVOR|ANYSWAPFIRST|ANYSWAP|ANYEXTRA|ANYCHANNELS|ANYSPACE,   PackHalfFromFloat },
#endif



};
