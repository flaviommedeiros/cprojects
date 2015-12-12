static struct vivi_fmt formats[] = {

    {
                .name = "RGB888 (24)",
                .fourcc = V4L2_PIX_FMT_RGB24, /* 24  RGB-8-8-8 */
                .depth = 24,
        },
    {
                .name = "RGBA8888 (32)",
                .fourcc = V4L2_PIX_FMT_RGB32, /* 24  RGBA-8-8-8-8 */
                .depth = 32,
    },
    {           .name = "12  Y/CbCr 4:2:0",
                .fourcc = V4L2_PIX_FMT_NV12,
                .depth = 12,
    },
    {           .name = "21  Y/CbCr 4:2:0",
                .fourcc = V4L2_PIX_FMT_NV21,
                .depth = 12,
    },
    {
                .name = "RGB565 (BE)",
                .fourcc = V4L2_PIX_FMT_RGB565X, /* rrrrrggg gggbbbbb */
                .depth = 16,
    },
#if 0
        {
            .name = "BGRA8888 (32)",
            .fourcc = V4L2_PIX_FMT_BGR32, /* 24  RGBA-8-8-8-8 */
            .depth = 32,
        },
        {
            .name = "BGR888 (24)",
            .fourcc = V4L2_PIX_FMT_BGR24, /* 24  BGR-8-8-8 */
            .depth = 24,
        },
        {
            .name = "YUV420P",
            .fourcc = V4L2_PIX_FMT_YUV420,
            .depth = 12,
        },
#endif
    };
