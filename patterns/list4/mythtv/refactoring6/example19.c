if (
#if CONFIG_TLS_PROTOCOL
        av_strstart(p->filename, "rtsps:", NULL) ||
#endif
        av_strstart(p->filename, "rtsp:", NULL))
        return AVPROBE_SCORE_MAX;
