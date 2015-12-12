static stream_buf_t bufs[BUF_MAX_NUM] = {
    {
        .reg_base = VLD_MEM_VIFIFO_REG_BASE,
        .type = BUF_TYPE_VIDEO,
        .buf_start = 0,
        .buf_size = 0,
        .first_tstamp = INVALID_PTS
    },
    {
        .reg_base = AIU_MEM_AIFIFO_REG_BASE,
        .type = BUF_TYPE_AUDIO,
        .buf_start = 0,
        .buf_size = 0,
        .first_tstamp = INVALID_PTS
    },
    {
        .reg_base = 0,
        .type = BUF_TYPE_SUBTITLE,
        .buf_start = 0,
        .buf_size = 0,
        .first_tstamp = INVALID_PTS
    },
    {
        .reg_base = 0,
        .type = BUF_TYPE_USERDATA,
        .buf_start = 0,
        .buf_size = 0,
        .first_tstamp = INVALID_PTS
    },
#if MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON8
    {
        .reg_base = HEVC_STREAM_REG_BASE,
        .type = BUF_TYPE_HEVC,
        .buf_start = 0,
        .buf_size = 0,
        .first_tstamp = INVALID_PTS
    },
#endif
};
