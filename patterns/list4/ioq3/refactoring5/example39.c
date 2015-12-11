#ifndef DISABLE_FLOAT_API
if (variable_duration == OPUS_FRAMESIZE_VARIABLE && frame_size >= Fs/200)
   {
      int LM = 3;
      LM = optimize_framesize(analysis_pcm, frame_size, C, Fs, bitrate_bps,
            0, subframe_mem, delay_compensation, downmix);
      while ((Fs/400<<LM)>frame_size)
         LM--;
      frame_size = (Fs/400<<LM);
   } else
#endif
   {
      frame_size = frame_size_select(frame_size, variable_duration, Fs);
   }
