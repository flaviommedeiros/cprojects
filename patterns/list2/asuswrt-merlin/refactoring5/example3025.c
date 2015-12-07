#ifdef DUMP_FORMAT_DATA
if (*args == 'd') {
                p->dump_iframe = 3;
            }
            else
#endif
            if (*args == 'I') {
                /* Dump only KEY (ie INTRA) frame */
                p->dump_iframe = 2;
            }
            else {
                if (*args == 'i') {
                    /* Print a 'I!' when a i-frame is encounter */
                    p->dump_iframe = 1;
                    ++args;
                }

                if (*args != '\0') {
                    p->frame_step = atoi(args);
                    if (p->frame_step <= 0) {
                        mp_msg(MSGT_VFILTER, MSGL_WARN, MSGTR_MPCODECS_ErrorParsingArgument);
                        return 0;
                    }
                }
            }
