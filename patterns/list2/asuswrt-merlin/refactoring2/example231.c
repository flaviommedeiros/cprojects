#if defined (VI_MODE)
if (rl_editing_mode != vi_mode)
#endif
    history_set_pos (oldpos);
