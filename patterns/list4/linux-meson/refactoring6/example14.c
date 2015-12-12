if ((cur_buf->duration == 0)
#if defined(CONFIG_AM_DEINTERLACE_SD_ONLY)
                || (cur_buf->width > 720)
#endif
               ) {
                di_pre_recycle_buf = 0;
                return;
            }
