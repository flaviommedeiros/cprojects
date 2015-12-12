if (vpts_expire(cur_dispbuf, vf)
#ifdef INTERLACE_FIELD_MATCH_PROCESS
            || interlace_field_type_match(vout_type, vf)
#endif
           ) {
            amlog_mask(LOG_MASK_TIMESTAMP,
                       "VIDEO_PTS = 0x%x, cur_dur=0x%x, next_pts=0x%x, scr = 0x%x\n",
                       timestamp_vpts_get(),
                       (cur_dispbuf) ? cur_dispbuf->duration : 0,
                       vf->pts,
                       timestamp_pcrscr_get());

            amlog_mask_if(toggle_cnt > 0, LOG_MASK_FRAMESKIP, "skipped\n");

            vf = video_vf_get();

            vsync_toggle_frame(vf);

            if (trickmode_fffb == 1) {
                atomic_set(&trickmode_framedone, 1);
                video_notify_flag |= VIDEO_NOTIFY_TRICK_WAIT;
                break;
            }

#ifdef SLOW_SYNC_REPEAT
            frame_repeat_count = 0;
#endif
            vf = video_vf_peek();
            
           // if(debug&0x10000){
                //return;
            //}
        } else {
#ifdef SLOW_SYNC_REPEAT
            /* check if current frame's duration has expired, in this example
             * it compares current frame display duration with 1/1/1/1.5 frame duration
             * every 4 frames there will be one frame play longer than usual.
             * you can adjust this array for any slow sync control as you want.
             * The playback can be smoother than previous method.
             */
            if (duration_expire(cur_dispbuf, vf, frame_repeat_count * vsync_pts_inc) && timestamp_pcrscr_enable_state()) {
                amlog_mask(LOG_MASK_SLOWSYNC,
                           "slow sync toggle, frame_repeat_count = %d\n",
                           frame_repeat_count);
                amlog_mask(LOG_MASK_SLOWSYNC,
                           "system time = 0x%x, video time = 0x%x\n",
                           timestamp_pcrscr_get(), timestamp_vpts_get());
                vf = video_vf_get();
                vsync_toggle_frame(vf);
                frame_repeat_count = 0;

                vf = video_vf_peek();
            } else
#endif
                /* setting video display property in pause mode */
                if (video_property_changed && cur_dispbuf) {
                    if (blackout) {
                        if (cur_dispbuf != &vf_local) {
                            vsync_toggle_frame(cur_dispbuf);
                        }
                    } else {
                        vsync_toggle_frame(cur_dispbuf);
                    }
                }

            break;
        }
