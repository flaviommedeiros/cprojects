if (avctx->skip_frame >= AVDISCARD_NONREF
#if FF_API_HURRY_UP
                || s->hurry_up
#endif
           )
            return 0;
