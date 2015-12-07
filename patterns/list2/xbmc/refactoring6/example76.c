if (read_32bitBE(0x30,streamFile) != read_32bitBE(0x10,streamFile)
#if 0
                /* this particular glitch only true for SFA, though it
                 * seems like something similar happens in Donkey Konga */
                /* loop start (Cstr, channel 1 & 2 headers) */
                || (read_32bitBE(0x0c,streamFile)+read_32bitLE(0x30,streamFile)) !=
                read_32bitBE(0x90,streamFile)
#endif
           )
            /* alternatively (Donkey Konga) the header loop is 0x0c+0x10 */
            if (
                    /* loop start (Cstr header and channel 1 header) */
                    read_32bitBE(0x30,streamFile) != read_32bitBE(0x10,streamFile)+
                    read_32bitBE(0x0c,streamFile))
                /* further alternatively (Donkey Konga), if we loop back to
                 * the very first frame 0x30 might be 0x00000002 (which
                 * is a *valid* std dsp loop start, imagine that) while 0x10
                 * is 0x00000000 */
                if (!(read_32bitBE(0x30,streamFile) == 2 &&
                            read_32bitBE(0x10,streamFile) == 0))
                    /* lest there be too few alternatives, in Mr. Driller we
                     * find that [0x30] + [0x0c] + 8 = [0x10]*2 */
                    if (!(double_loop_end &&
                            read_32bitBE(0x30,streamFile) +
                            read_32bitBE(0x0c,streamFile) + 8 ==
                            read_32bitBE(0x10,streamFile)*2))
                        goto fail;
