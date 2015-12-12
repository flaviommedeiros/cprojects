const u32 canvas_tab[4] = {
#if MESON_CPU_TYPE >= MESON_CPU_TYPE_MESON6  
        0x010100, 0x030302, 0x050504, 0x070706
#else
        0x020100, 0x050403, 0x080706, 0x0b0a09
#endif
    };
