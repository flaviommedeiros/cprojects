#if defined(CLIP_LIGHT_FANS)
if (ptile._lightingCache.isValid(game_frame_all, frame_skip))
#else
        // let the function clip all tile updates
        if (ptile._lightingCache.isValid(game_frame_all))
#endif
        {
            continue;
        }
