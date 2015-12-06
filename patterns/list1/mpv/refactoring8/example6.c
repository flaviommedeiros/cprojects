static const struct img_writer img_writers[] = {
    { "png", write_lavc, .lavc_codec = AV_CODEC_ID_PNG },
    { "ppm", write_lavc, .lavc_codec = AV_CODEC_ID_PPM },
    { "pgm", write_lavc, .lavc_codec = AV_CODEC_ID_PGM },
    { "pgmyuv", write_lavc, .lavc_codec = AV_CODEC_ID_PGMYUV },
    { "tga", write_lavc, .lavc_codec = AV_CODEC_ID_TARGA },
#if HAVE_JPEG
    { "jpg", write_jpeg },
    { "jpeg", write_jpeg },
#endif
};
