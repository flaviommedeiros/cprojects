switch (pixel_format) {
    case kCVPixelFormatType_420YpCbCr8Planar: vt->tmp_frame->format = AV_PIX_FMT_YUV420P; break;
    case kCVPixelFormatType_422YpCbCr8:       vt->tmp_frame->format = AV_PIX_FMT_UYVY422; break;
    case kCVPixelFormatType_32BGRA:           vt->tmp_frame->format = AV_PIX_FMT_BGRA; break;
#ifdef kCFCoreFoundationVersionNumber10_7
    case kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange: vt->tmp_frame->format = AV_PIX_FMT_NV12; break;
#endif
    default:
        av_get_codec_tag_string(codec_str, sizeof(codec_str), s->codec_tag);
        av_log(NULL, AV_LOG_ERROR,
               "%s: Unsupported pixel format: %s\n", codec_str, videotoolbox_pixfmt);
        return AVERROR(ENOSYS);
    }
