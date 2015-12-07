# ifdef SIXTY_FOUR_BIT
if (l & 0xffffffff00000000LL) {
        if (l & 0xffff000000000000LL) {
            if (l & 0xff00000000000000LL) {
                return (bits[(int)(l >> 56)] + 56);
            } else
                return (bits[(int)(l >> 48)] + 48);
        } else {
            if (l & 0x0000ff0000000000LL) {
                return (bits[(int)(l >> 40)] + 40);
            } else
                return (bits[(int)(l >> 32)] + 32);
        }
    } else
# endif
#endif
    {
#if defined(THIRTY_TWO_BIT) || defined(SIXTY_FOUR_BIT) || defined(SIXTY_FOUR_BIT_LONG)
        if (l & 0xffff0000L) {
            if (l & 0xff000000L)
                return (bits[(int)(l >> 24L)] + 24);
            else
                return (bits[(int)(l >> 16L)] + 16);
        } else
#endif
        {
#if defined(THIRTY_TWO_BIT) || defined(SIXTY_FOUR_BIT) || defined(SIXTY_FOUR_BIT_LONG)
            if (l & 0xff00L)
                return (bits[(int)(l >> 8)] + 8);
            else
#endif
                return (bits[(int)(l)]);
        }
    }
