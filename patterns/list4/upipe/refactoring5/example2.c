#ifdef HAVE_X264_MPEG2
if (upipe_x264_mpeg2_enabled(upipe)) {
            switch (params->i_level_idc) {
                case X264_MPEG2_LEVEL_LOW:
                    max_octetrate = 4000000 / 8;
                    max_bs = 475136 / 8;
                    break;
                default:
                    upipe_warn_va(upipe, "unknown level %"PRIu8,
                                  params->i_level_idc);
                    /* intended fall-through */
                case X264_MPEG2_LEVEL_MAIN:
                    max_octetrate = 15000000 / 8;
                    max_bs = 1835008 / 8;
                    break;
                case X264_MPEG2_LEVEL_HIGH_1440:
                    max_octetrate = 60000000 / 8;
                    max_bs = 7340032 / 8;
                    break;
                case X264_MPEG2_LEVEL_HIGH:
                    max_octetrate = 80000000 / 8;
                    max_bs = 9781248 / 8;
                    break;
                case X264_MPEG2_LEVEL_HIGHP:
                    /* ISO/IEC JTC1/SC29/WG11 MPEG2007/m14868 */
                    max_octetrate = 120000000 / 8;
                    max_bs = 14671872 / 8;
                    break;
            }
        } else
#endif
        {
            switch (params->i_level_idc) {
                case 10:
                    max_octetrate = 64000 / 8;
                    max_bs = 175000 / 8;
                    break;
                case 11:
                    max_octetrate = 192000 / 8;
                    max_bs = 500000 / 8;
                    break;
                case 12:
                    max_octetrate = 384000 / 8;
                    max_bs = 1000000 / 8;
                    break;
                case 13:
                    max_octetrate = 768000 / 8;
                    max_bs = 2000000 / 8;
                    break;
                case 20:
                    max_octetrate = 2000000 / 8;
                    max_bs = 2000000 / 8;
                    break;
                case 21:
                case 22:
                    max_octetrate = 4000000 / 8;
                    max_bs = 4000000 / 8;
                    break;
                case 30:
                    max_octetrate = 10000000 / 8;
                    max_bs = 10000000 / 8;
                    break;
                case 31:
                    max_octetrate = 14000000 / 8;
                    max_bs = 14000000 / 8;
                    break;
                case 32:
                case 40:
                    max_octetrate = 20000000 / 8;
                    max_bs = 20000000 / 8;
                    break;
                case 41:
                case 42:
                    max_octetrate = 50000000 / 8;
                    max_bs = 62500000 / 8;
                    break;
                case 50:
                    max_octetrate = 135000000 / 8;
                    max_bs = 135000000 / 8;
                    break;
                default:
                    upipe_warn_va(upipe, "unknown level %"PRIu8,
                                  params->i_level_idc);
                    /* intended fall-through */
                case 51:
                case 52:
                    max_octetrate = 240000000 / 8;
                    max_bs = 240000000 / 8;
                    break;
            }
        }
