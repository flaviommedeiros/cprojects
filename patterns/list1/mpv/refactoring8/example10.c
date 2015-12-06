static int demux_open_lavf(demuxer_t *demuxer, enum demux_check check)
{
    struct MPOpts *opts = demuxer->opts;
    struct demux_lavf_opts *lavfdopts = opts->demux_lavf;
    AVFormatContext *avfc;
    AVDictionaryEntry *t = NULL;
    float analyze_duration = 0;
    int i;

    if (lavf_check_file(demuxer, check) < 0)
        return -1;

    lavf_priv_t *priv = demuxer->priv;
    if (!priv)
        return -1;

    avfc = avformat_alloc_context();
    if (!avfc)
        return -1;

    if (lavfdopts->cryptokey)
        parse_cryptokey(avfc, lavfdopts->cryptokey);
    if (lavfdopts->genptsmode)
        avfc->flags |= AVFMT_FLAG_GENPTS;
    if (opts->index_mode != 1)
        avfc->flags |= AVFMT_FLAG_IGNIDX;

#if LIBAVFORMAT_VERSION_MICRO >= 100
    /* Keep side data as side data instead of mashing it into the packet
     * stream.
     * Note: Libav doesn't have this horrible insanity. */
    av_opt_set(avfc, "fflags", "+keepside", 0);
#endif

    if (lavfdopts->probesize) {
        if (av_opt_set_int(avfc, "probesize", lavfdopts->probesize, 0) < 0)
            MP_ERR(demuxer, "couldn't set option probesize to %u\n",
                   lavfdopts->probesize);
    }

    if (priv->format_hack.analyzeduration)
        analyze_duration = priv->format_hack.analyzeduration;
    if (lavfdopts->analyzeduration)
        analyze_duration = lavfdopts->analyzeduration;
    if (analyze_duration > 0) {
        if (av_opt_set_int(avfc, "analyzeduration",
                           analyze_duration * AV_TIME_BASE, 0) < 0)
            MP_ERR(demuxer, "demux_lavf, couldn't set option "
                   "analyzeduration to %f\n", analyze_duration);
    }

    AVDictionary *dopts = NULL;

    if ((priv->avif_flags & AVFMT_NOFILE) ||
        demuxer->stream->type == STREAMTYPE_AVDEVICE ||
        priv->format_hack.no_stream)
    {
        mp_setup_av_network_options(&dopts, demuxer->global, demuxer->log, opts);
        // This might be incorrect.
        demuxer->seekable = true;
    } else {
        void *buffer = av_malloc(lavfdopts->buffersize);
        if (!buffer)
            return -1;
        priv->pb = avio_alloc_context(buffer, lavfdopts->buffersize, 0,
                                      demuxer, mp_read, NULL, mp_seek);
        if (!priv->pb) {
            av_free(buffer);
            return -1;
        }
        priv->pb->read_seek = mp_read_seek;
        priv->pb->seekable = demuxer->seekable ? AVIO_SEEKABLE_NORMAL : 0;
        avfc->pb = priv->pb;
        if (stream_control(demuxer->stream, STREAM_CTRL_HAS_AVSEEK, NULL) > 0)
            demuxer->seekable = true;
    }

    if (matches_avinputformat_name(priv, "rtsp")) {
        const char *transport = NULL;
        switch (opts->network_rtsp_transport) {
        case 1: transport = "udp";  break;
        case 2: transport = "tcp";  break;
        case 3: transport = "http"; break;
        }
        if (transport)
            av_dict_set(&dopts, "rtsp_transport", transport, 0);
    }

    guess_and_set_vobsub_name(demuxer, &dopts);

    avfc->interrupt_callback = (AVIOInterruptCB){
        .callback = interrupt_cb,
        .opaque = demuxer,
    };

    mp_set_avdict(&dopts, lavfdopts->avopts);

    if (avformat_open_input(&avfc, priv->filename, priv->avif, &dopts) < 0) {
        MP_ERR(demuxer, "avformat_open_input() failed\n");
        av_dict_free(&dopts);
        return -1;
    }

    mp_avdict_print_unset(demuxer->log, MSGL_V, dopts);
    av_dict_free(&dopts);

    priv->avfc = avfc;
    if (avformat_find_stream_info(avfc, NULL) < 0) {
        MP_ERR(demuxer, "av_find_stream_info() failed\n");
        return -1;
    }

    MP_VERBOSE(demuxer, "avformat_find_stream_info() finished after %"PRId64
               " bytes.\n", stream_tell(demuxer->stream));

    for (i = 0; i < avfc->nb_chapters; i++) {
        AVChapter *c = avfc->chapters[i];
        t = av_dict_get(c->metadata, "title", NULL, 0);
        int index = demuxer_add_chapter(demuxer, t ? t->value : "",
                                        c->start * av_q2d(c->time_base), i);
        mp_tags_copy_from_av_dictionary(demuxer->chapters[index].metadata, c->metadata);
    }

    add_new_streams(demuxer);

    // Often useful with OGG audio-only files, which have metadata in the audio
    // track metadata instead of the main metadata.
    if (demuxer->num_streams == 1) {
        priv->merge_track_metadata = true;
        for (int n = 0; n < priv->num_streams; n++) {
            if (priv->streams[n])
                mp_tags_copy_from_av_dictionary(demuxer->metadata, avfc->streams[n]->metadata);
        }
    }

    mp_tags_copy_from_av_dictionary(demuxer->metadata, avfc->metadata);
    update_metadata(demuxer, NULL);

    demuxer->ts_resets_possible =
        priv->avif_flags & (AVFMT_TS_DISCONT | AVFMT_NOTIMESTAMPS);

    demuxer->start_time = priv->avfc->start_time == AV_NOPTS_VALUE ?
                          0 : (double)priv->avfc->start_time / AV_TIME_BASE;

    demuxer->allow_refresh_seeks = matches_avinputformat_name(priv, "mp4");
    demuxer->fully_read = priv->format_hack.fully_read;

    return 0;
}
