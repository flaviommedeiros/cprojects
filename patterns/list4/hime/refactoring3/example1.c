switch (xkey) {
     case XK_Control_L:
     case XK_Control_R:
       if (key_press_ctrl && tss.pre_selN) {
         if (!test_mode) {
           tss.ctrl_pre_sel = TRUE;
         }
	 key_press_ctrl = FALSE;
         return 1;
       } else
         return 0;
#if 1
     case XK_Shift_L:
     case XK_Shift_R:
// dbg("release xkey %x\n", xkey);
        if (((tsin_chinese_english_toggle_key == TSIN_CHINESE_ENGLISH_TOGGLE_KEY_Shift) ||
             (tsin_chinese_english_toggle_key == TSIN_CHINESE_ENGLISH_TOGGLE_KEY_ShiftL && xkey == XK_Shift_L) ||
             (tsin_chinese_english_toggle_key == TSIN_CHINESE_ENGLISH_TOGGLE_KEY_ShiftR && xkey == XK_Shift_R)) &&
	     key_press_alt) {
          if (!test_mode) {
            tsin_toggle_eng_ch();
          }
	  key_press_alt = FALSE;
          return 1;
        } else
          return 0;
#endif
     default:
        return 0;
  }
