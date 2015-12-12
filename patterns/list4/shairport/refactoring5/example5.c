#ifdef FANCY_RESAMPLING
if (fancy_resampling) {
            int i;
            pthread_mutex_lock(&vol_mutex);
            for (i=0; i<2*FRAME_BYTES(frame_size); i++) {
                frame[i] = (float)inbuf[i] / 32768.0;
                frame[i] *= volume;
            }
            pthread_mutex_unlock(&vol_mutex);
            srcdat.src_ratio = bf_playback_rate;
            src_process(src, &srcdat);
            assert(srcdat.input_frames_used == FRAME_BYTES(frame_size));
            src_float_to_short_array(outframe, outbuf, FRAME_BYTES(frame_size)*2);
            play_samples = srcdat.output_frames_gen;
        } else
#endif
            play_samples = stuff_buffer(bf_playback_rate, inbuf, outbuf);
