#ifdef HAVE_X264_MPEG2
if (upipe_x264_mpeg2_enabled(upipe)) {
        params->vui.i_aspect_ratio_information = upipe_x264->mpeg2_ar;
    } else
#endif
    {
        params->vui.i_sar_width = upipe_x264->sar.num;
        params->vui.i_sar_height = upipe_x264->sar.den;
        params->vui.i_overscan = upipe_x264->overscan ? 2 : 1;
    }
