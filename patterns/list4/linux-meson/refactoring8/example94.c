const u32 canvas_tab[4] = {
#ifdef NV21
                0x010100, 0x040403, 0x070706, 0x0a0a09
#else
                0x020100, 0x050403, 0x080706, 0x0b0a09
#endif
        };
