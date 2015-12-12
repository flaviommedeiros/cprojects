const AVDVProfile *av_dv_codec_profile2(int width, int height,
                                       enum AVPixelFormat pix_fmt,
                                       AVRational frame_rate)
{
    const AVDVProfile *p = NULL;
#if CONFIG_DVPROFILE
    int i;
    /* frame rate is necessary to select between 720p50 and 720p60 profiles */
    int invalid_framerate = frame_rate.num == 0 || frame_rate.den == 0;

    for (i = 0; i < FF_ARRAY_ELEMS(dv_profiles); i++)
        if (height  == dv_profiles[i].height  &&
            pix_fmt == dv_profiles[i].pix_fmt &&
            width   == dv_profiles[i].width)
        {
            if( invalid_framerate || av_div_q(dv_profiles[i].time_base, frame_rate).num == 1 )
                return &dv_profiles[i];

            if(!p)
                p = &dv_profiles[i];
        }
#endif

    return p;
}
