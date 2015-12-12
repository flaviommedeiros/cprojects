switch (dev) {                                  /* case on dev */

        case 000:                                       /* I/O wait */
            break;

        case 001:
            if (IR & 003700)                            /* DECtape */
                io_data = dt (IR, dev, IO);
            else io_data = ptr (IR, dev, IO);           /* paper tape rdr */
            break;

        case 002: case 030:                             /* paper tape rdr */
            io_data = ptr (IR, dev, IO);
            break;

        case 003:                                       /* typewriter */
            io_data = tto (IR, dev, IO);
            break;

        case 004:                                       /* keyboard */
            io_data = tti (IR, dev, IO);
            break;

        case 005: case 006:                             /* paper tape punch */
            io_data = ptp (IR, dev, IO);
            break;

#ifdef USE_DISPLAY
        case 007:                                       /* display */
            io_data = dpy (IR, dev, IO, AC);
            break;
#endif
        case 010:                                       /* leave ring mode */
            if (cpu_unit.flags & UNIT_1D)
                PF = PF & ~PF_RNG;
            else reason = stop_inst;
            break;

        case 011:                                       /* enter ring mode */
            if (cpu_unit.flags & UNIT_1D)
                PF = PF | PF_RNG;
            else
#ifdef USE_DISPLAY
                io_data = spacewar (IR, dev, IO);
#else
                reason = stop_inst;
#endif
            break;

       case 022:                                        /* data comm sys */
           io_data = dcs (IR, dev, IO);
           break;

        case 032:                                       /* clock */
            io_data = clk (IR, dev, IO);
            break;

        case 033:                                       /* check status */
            io_data = iosta | ((sbs & SB_ON)? IOS_SQB: 0);
            break;

        case 035:                                       /* check trap buf */
            if (cpu_unit.flags & UNIT_1D45) {           /* SN 45? */
                io_data = rtb;
                rtb = 0;
                }
            else reason = stop_inst;
            break;

        case 045:                                       /* line printer */
            io_data = lpt (IR, dev, IO);
            break;

        case 050:                                       /* deact seq break */
            if (cpu_unit.flags & UNIT_SBS)
                sbs_enb &= ~SBS_MASK (pulse & SBS_LVL_MASK);
            else reason = stop_inst;
            break;

        case 051:                                       /* act seq break */
            if (cpu_unit.flags & UNIT_SBS)
                sbs_enb |= SBS_MASK (pulse & SBS_LVL_MASK);
            else reason = stop_inst;
            break;

        case 052:                                       /* start seq break */
            if (cpu_unit.flags & UNIT_SBS)
                sbs_req |= SBS_MASK (pulse & SBS_LVL_MASK);
            else reason = stop_inst;
            break;

        case 053:                                       /* clear all chan */
            if (cpu_unit.flags & UNIT_SBS)
                sbs_enb = 0;
            else reason = stop_inst;
            break;

        case 054:                                       /* seq brk off */
            sbs = sbs & ~SB_ON;
            break;

        case 055:                                       /* seq brk on */
            sbs = sbs | SB_ON;
            break;

        case 056:                                       /* clear seq brk */
            sbs = 0;                                    /* clear PI */
            sbs_req = 0;
            sbs_enb = 0;
            sbs_act = 0;
            break;

        case 061: case 062: case 063:                   /* drum */
            io_data = drm (IR, dev, IO);
            break;

        case 064:                                       /* drum/leave rm */
            if (cpu_unit.flags & UNIT_1D)
                rm = 0;
            else io_data = drm (IR, dev, IO);
            break;

        case 065:                                       /* enter rm */
            if (cpu_unit.flags & UNIT_1D) {
                rm = 1;
                rmask = IO;
                }
            else reason = stop_inst;
            break;

        case 066:                                       /* rename mem */
            if (cpu_unit.flags & UNIT_1D45) {           /* SN45? */
                int32 from = (IR >> 9) & RM45_M_BNK;
                int32 to = (IR >> 6) & RM45_M_BNK;
                rname[from] = to;
                }
            else reason = stop_inst;
            break;

        case 067:                                       /* reset renaming */
            if (cpu_unit.flags & UNIT_1D45) {           /* SN45 */
                for (i = 0; i < RN45_SIZE; i++)
                    rname[i] = i;
                }
            else reason = stop_inst;
            break;

        case 074:                                       /* extend mode */
            extm = (IR >> 11) & 1;                      /* set from IR<6> */
            break;

        default:                                        /* undefined */
            reason = stop_inst;
            break;
            }
