#ifndef DISABLE_FLOAT_API
if (st->silk_mode.complexity >= 10 && st->Fs==48000)
#else
    if (st->silk_mode.complexity >= 7 && st->Fs==48000)
#endif
    {
       analysis_read_pos_bak = st->analysis.read_pos;
       analysis_read_subframe_bak = st->analysis.read_subframe;
       run_analysis(&st->analysis, celt_mode, analysis_pcm, analysis_size, frame_size,
             c1, c2, analysis_channels, st->Fs,
             lsb_depth, downmix, &analysis_info);
    }
