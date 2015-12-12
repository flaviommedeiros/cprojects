if (((READ_VREG(VLD_MEM_VIFIFO_CONTROL) & 0x100) == 0) && // decoder has input
        (state == RECEIVER_INACTIVE) &&                       // receiver has no buffer to recycle
        (kfifo_is_empty(&display_q)) &&                       // no buffer in display queue
        (kfifo_is_empty(&recycle_q)) &&                       // no buffer to recycle
        (READ_VREG(MS_ID) & 0x100)
#ifdef CONFIG_H264_2K4K_SINGLE_CORE
        && (READ_VREG(VDEC2_MS_ID) & 0x100)                   // with both decoder have started decoding
#endif
        && first_i_recieved) {
        if (++error_watchdog_count == ERROR_RESET_COUNT) {    // and it lasts for a while
            printk("H264 4k2k decoder fatal error watchdog.\n");
            fatal_error = DECODER_FATAL_ERROR_UNKNOW;
        }
    } else {
      error_watchdog_count = 0;
    }
