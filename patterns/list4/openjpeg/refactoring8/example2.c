static cmsFormattersFloat InputFormattersFloat[] = {

    //    Type                                          Mask                  Function
    //  ----------------------------   ------------------------------------  ----------------------------
    {     TYPE_Lab_DBL,                                ANYPLANAR|ANYEXTRA,   UnrollLabDoubleToFloat},
    {     TYPE_Lab_FLT,                                ANYPLANAR|ANYEXTRA,   UnrollLabFloatToFloat},

    {     TYPE_XYZ_DBL,                                ANYPLANAR|ANYEXTRA,   UnrollXYZDoubleToFloat},
    {     TYPE_XYZ_FLT,                                ANYPLANAR|ANYEXTRA,   UnrollXYZFloatToFloat},

    {     FLOAT_SH(1)|BYTES_SH(4), ANYPLANAR|ANYSWAPFIRST|ANYSWAP|ANYEXTRA|
                                                      ANYCHANNELS|ANYSPACE,  UnrollFloatsToFloat},

    {     FLOAT_SH(1)|BYTES_SH(0), ANYPLANAR|ANYSWAPFIRST|ANYSWAP|ANYEXTRA|
                                                        ANYCHANNELS|ANYSPACE,  UnrollDoublesToFloat},
#ifndef CMS_NO_HALF_SUPPORT 
    {     FLOAT_SH(1)|BYTES_SH(2), ANYPLANAR|ANYSWAPFIRST|ANYSWAP|ANYEXTRA|
                                                        ANYCHANNELS|ANYSPACE,  UnrollHalfToFloat},
#endif
};
