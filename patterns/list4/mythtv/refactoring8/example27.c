static const AVOption options[] = {
#if HAVE_LIBDC1394_1
    { "channel", "", offsetof(dc1394_data, channel), AV_OPT_TYPE_INT, {.i64 = 0}, 0, INT_MAX, AV_OPT_FLAG_DECODING_PARAM },
#endif
    { "video_size", "A string describing frame size, such as 640x480 or hd720.", OFFSET(video_size), AV_OPT_TYPE_STRING, {.str = "qvga"}, 0, 0, DEC },
    { "pixel_format", "", OFFSET(pixel_format), AV_OPT_TYPE_STRING, {.str = "uyvy422"}, 0, 0, DEC },
    { "framerate", "", OFFSET(framerate), AV_OPT_TYPE_STRING, {.str = "ntsc"}, 0, 0, DEC },
    { NULL },
};
