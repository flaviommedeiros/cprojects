switch (avs->vi->pixel_type) {
#ifdef USING_AVISYNTH
    case AVS_CS_YV24:
        st->codec->pix_fmt = AV_PIX_FMT_YUV444P;
        planar             = 1;
        break;
    case AVS_CS_YV16:
        st->codec->pix_fmt = AV_PIX_FMT_YUV422P;
        planar             = 1;
        break;
    case AVS_CS_YV411:
        st->codec->pix_fmt = AV_PIX_FMT_YUV411P;
        planar             = 1;
        break;
    case AVS_CS_Y8:
        st->codec->pix_fmt = AV_PIX_FMT_GRAY8;
        planar             = 2;
        break;
#endif
    case AVS_CS_BGR24:
        st->codec->pix_fmt = AV_PIX_FMT_BGR24;
        break;
    case AVS_CS_BGR32:
        st->codec->pix_fmt = AV_PIX_FMT_RGB32;
        break;
    case AVS_CS_YUY2:
        st->codec->pix_fmt = AV_PIX_FMT_YUYV422;
        break;
    case AVS_CS_YV12:
        st->codec->pix_fmt = AV_PIX_FMT_YUV420P;
        planar             = 1;
        break;
    case AVS_CS_I420: // Is this even used anywhere?
        st->codec->pix_fmt = AV_PIX_FMT_YUV420P;
        planar             = 1;
        break;
    default:
        av_log(s, AV_LOG_ERROR,
               "unknown AviSynth colorspace %d\n", avs->vi->pixel_type);
        avs->error = 1;
        return AVERROR_UNKNOWN;
    }
