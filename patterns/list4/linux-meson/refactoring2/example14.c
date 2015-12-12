#if defined(CONFIG_ARCH_MESON)
if ((temp & 0xf) != (status | 0x9))
#elif defined(CONFIG_ARCH_MESON2)
        if ((temp & 0xf) != (status | 0x1))
#endif
            return;
