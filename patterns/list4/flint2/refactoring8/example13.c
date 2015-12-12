static const mp_limb_t max_base[] = { 
#ifdef FLINT64
                        UWORD(0), UWORD_MAX, UWORD(4294967296), UWORD(2642245), UWORD(65536),
                        UWORD(7131), UWORD(1625), UWORD(565), UWORD(256), UWORD(138), UWORD(84),
                        UWORD(56), UWORD(40), UWORD(30), UWORD(23), UWORD(19), UWORD(16),
                        UWORD(13), UWORD(11), UWORD(10), UWORD(9), UWORD(8), UWORD(7),
                        UWORD(6), UWORD(6), UWORD(5), UWORD(5), UWORD(5), UWORD(4), UWORD(4),
                        UWORD(4), UWORD(4), UWORD(4), UWORD(3), UWORD(3), UWORD(3), UWORD(3),
                        UWORD(3), UWORD(3), UWORD(3), UWORD(3), UWORD(2), UWORD(2), UWORD(2),
                        UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2),
                        UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2),
                        UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2)
#else
                        UWORD(0), UWORD(4294967295),  UWORD(65535), UWORD(1625), UWORD(255), 
                        UWORD(84),  UWORD(40), UWORD(23), UWORD(15), UWORD(11), UWORD(9),
                        UWORD(7), UWORD(6), UWORD(5), UWORD(4), UWORD(4), UWORD(3), UWORD(3),
                        UWORD(3), UWORD(3), UWORD(3), UWORD(2), UWORD(2), UWORD(2), UWORD(2),
                        UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2), UWORD(2)
#endif
                                                        };
