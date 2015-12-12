#ifdef VIDEO_AUTO_FLUSH
if (video_auto_flush_state == VIDEO_AUTO_FLUSH_TRIGGER) {
            next_action = SEARCH_START_CODE_VIDEO_FLUSH;
            video_auto_flush_state = VIDEO_AUTO_FLUSH_DONE;
        } else
#endif

        next_action = SEARCH_START_CODE;
