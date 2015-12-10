#if 1
if (!check_recording_time(ost))
#else
    if (ost->frame_number >= ost->max_frames)
#endif
        return;
