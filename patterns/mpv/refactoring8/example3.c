static const format_t format_table[] = {
    {WL_SHM_FORMAT_ARGB8888, IMGFMT_BGRA}, // 8b 8g 8r 8a
    {WL_SHM_FORMAT_XRGB8888, IMGFMT_BGR0},
    {WL_SHM_FORMAT_RGB332,   IMGFMT_RGB8}, // 3b 3g 2r
    {WL_SHM_FORMAT_BGR233,   IMGFMT_BGR8}, // 3r 3g 3b,
#if BYTE_ORDER == LITTLE_ENDIAN
    {WL_SHM_FORMAT_XRGB4444, IMGFMT_RGB444}, // 4b 4g 4r 4a
    {WL_SHM_FORMAT_XBGR4444, IMGFMT_BGR444}, // 4r 4g 4b 4a
    {WL_SHM_FORMAT_ARGB4444, IMGFMT_RGB444},
    {WL_SHM_FORMAT_ABGR4444, IMGFMT_BGR444},
    {WL_SHM_FORMAT_XRGB1555, IMGFMT_RGB555}, // 5b 5g 5r 1a
    {WL_SHM_FORMAT_XBGR1555, IMGFMT_BGR555}, // 5r 5g 5b 1a
    {WL_SHM_FORMAT_ARGB1555, IMGFMT_RGB555},
    {WL_SHM_FORMAT_ABGR1555, IMGFMT_BGR555},
    {WL_SHM_FORMAT_RGB565,   IMGFMT_RGB565}, // 5b 6g 5r
    {WL_SHM_FORMAT_BGR565,   IMGFMT_BGR565}, // 5r 6g 5b
#else
    {WL_SHM_FORMAT_RGBX4444, IMGFMT_BGR444}, // 4a 4b 4g 4r
    {WL_SHM_FORMAT_BGRX4444, IMGFMT_RGB444}, // 4a 4r 4g 4b
    {WL_SHM_FORMAT_RGBA4444, IMGFMT_BGR444},
    {WL_SHM_FORMAT_BGRA4444, IMGFMT_RGB444},
    {WL_SHM_FORMAT_RGBX5551, IMGFMT_BGR555}, // 1a 5g 5b 5r
    {WL_SHM_FORMAT_BGRX5551, IMGFMT_RGB555}, // 1a 5r 5g 5b
    {WL_SHM_FORMAT_RGBA5551, IMGFMT_BGR555},
    {WL_SHM_FORMAT_BGRA5551, IMGFMT_RGB555},
#endif
    {WL_SHM_FORMAT_RGB888,   IMGFMT_BGR24}, // 8b 8g 8r
    {WL_SHM_FORMAT_BGR888,   IMGFMT_RGB24}, // 8r 8g 8b
    {WL_SHM_FORMAT_XBGR8888, IMGFMT_RGB0},
    {WL_SHM_FORMAT_RGBX8888, IMGFMT_0BGR},
    {WL_SHM_FORMAT_BGRX8888, IMGFMT_0RGB},
    {WL_SHM_FORMAT_ABGR8888, IMGFMT_RGBA},
    {WL_SHM_FORMAT_RGBA8888, IMGFMT_ABGR},
    {WL_SHM_FORMAT_BGRA8888, IMGFMT_ARGB},
};
