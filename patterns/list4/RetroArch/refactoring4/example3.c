#ifdef HAVE_FFMPEG
if (g_extern.recording && g_settings.video.post_filter_record)
         recording_dump_frame(g_extern.filter.buffer, owidth, oheight, g_extern.filter.pitch);
