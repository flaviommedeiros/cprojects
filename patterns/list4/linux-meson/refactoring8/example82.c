static struct class_attribute audiodsp_attrs[] = {
    __ATTR_RO(codec_fmt),
#ifdef CONFIG_ARCH_MESON1
    __ATTR_RO(codec_mips),
#endif
    __ATTR(codec_fatal_err, S_IRUGO | S_IWUSR | S_IWGRP,
    codec_fatal_err_show, codec_fatal_err_store),
    __ATTR_RO(swap_buf_ptr),
    __ATTR_RO(dsp_working_status),
    __ATTR(digital_raw, S_IRUGO | S_IWUSR | S_IWGRP, digital_raw_show,
    digital_raw_store),
    __ATTR(digital_codec, S_IRUGO | S_IWUSR | S_IWGRP, digital_codec_show,
    digital_codec_store),
    __ATTR(dec_option, S_IRUGO | S_IWUSR, dec_option_show,
    dec_option_store),
    __ATTR(print_flag, S_IRUGO | S_IWUSR, print_flag_show,
    print_flag_store),
    __ATTR(ac3_drc_control, S_IRUGO | S_IWUSR | S_IWGRP,
    ac3_drc_control_show, ac3_drc_control_store),
    __ATTR(dsp_debug, S_IRUGO | S_IWUSR, dsp_debug_show, dsp_debug_store),
    __ATTR(dts_dec_control, S_IRUGO | S_IWUSR, dts_dec_control_show,
    dts_dec_control_store),
    __ATTR(skip_rawbytes, S_IRUGO | S_IWUSR, skip_rawbytes_show,
    skip_rawbytes_store),
    __ATTR_RO(pcm_left_len),
    __ATTR_RO(audio_samesource),
    __ATTR_NULL
};
