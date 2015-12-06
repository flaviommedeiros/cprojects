switch (fe_info.type) {
    case FE_OFDM:
        if (freq < 1000000)
            freq *= 1000UL;
        feparams.frequency = freq;
        feparams.inversion = specInv;
        feparams.u.ofdm.bandwidth = bandwidth;
        feparams.u.ofdm.code_rate_HP = HP_CodeRate;
        feparams.u.ofdm.code_rate_LP = LP_CodeRate;
        feparams.u.ofdm.constellation = modulation;
        feparams.u.ofdm.transmission_mode = TransmissionMode;
        feparams.u.ofdm.guard_interval = guardInterval;
        feparams.u.ofdm.hierarchy_information = hier;
        MP_VERBOSE(priv, "tuning DVB-T to %d Hz, bandwidth: %d\n",
                   freq, bandwidth);
        if (ioctl(fd_frontend, FE_SET_FRONTEND, &feparams) < 0) {
            MP_ERR(priv, "ERROR tuning channel\n");
            return -1;
        }
        break;
    case FE_QPSK:
        // DVB-S
        if (freq > 2200000) {
            // this must be an absolute frequency
            if (freq < SLOF) {
                freq = feparams.frequency = (freq - LOF1);
                hi_lo = 0;
            } else {
                freq = feparams.frequency = (freq - LOF2);
                hi_lo = 1;
            }
        } else {
            // this is an L-Band frequency
            feparams.frequency = freq;
        }

        feparams.inversion = specInv;
        feparams.u.qpsk.symbol_rate = srate;
        feparams.u.qpsk.fec_inner = HP_CodeRate;
        dfd = fd_frontend;

        MP_VERBOSE(priv, "tuning DVB-S%sto Freq: %u, Pol: %c Srate: %d, "
                   "22kHz: %s, LNB:  %d\n", is_dvb_s2 ? "2 " : " ", freq,
                   pol, srate, hi_lo ? "on" : "off", diseqc);

        if (do_diseqc(dfd, diseqc, (pol == 'V' ? 1 : 0), hi_lo) == 0) {
            MP_VERBOSE(priv, "DISEQC setting succeeded\n");
        } else {
            MP_ERR(priv, "DISEQC setting failed\n");
            return -1;
        }
        usleep(100000);

#ifdef DVB_USE_S2API
        /* S2API is the DVB API new since 2.6.28.
         * It is needed to tune to new delivery systems, e.g. DVB-S2.
         * It takes a struct with a list of pairs of command + parameter.
         */

        fe_delivery_system_t delsys = SYS_DVBS;
        if (is_dvb_s2)
            delsys = SYS_DVBS2;
        fe_rolloff_t rolloff = ROLLOFF_AUTO;

        struct dtv_property p[] = {
            { .cmd = DTV_DELIVERY_SYSTEM, .u.data = delsys },
            { .cmd = DTV_FREQUENCY, .u.data = freq },
            { .cmd = DTV_MODULATION, .u.data = modulation },
            { .cmd = DTV_SYMBOL_RATE, .u.data = srate },
            { .cmd = DTV_INNER_FEC, .u.data = HP_CodeRate },
            { .cmd = DTV_INVERSION, .u.data = specInv },
            { .cmd = DTV_ROLLOFF, .u.data = rolloff },
            { .cmd = DTV_PILOT, .u.data = PILOT_AUTO },
            { .cmd = DTV_STREAM_ID, .u.data = stream_id },
            { .cmd = DTV_TUNE },
        };
        struct dtv_properties cmdseq = {
            .num = sizeof(p) / sizeof(p[0]),
            .props = p
        };
        MP_VERBOSE(priv, "Tuning via S2API, channel is DVB-S%s.\n",
                   is_dvb_s2 ? "2" : "");
        if ((ioctl(fd_frontend, FE_SET_PROPERTY, &cmdseq)) == -1) {
            MP_ERR(priv, "ERROR tuning channel\n");
            return -1;
        }
#else
        MP_VERBOSE(priv, "Tuning via DVB-API version 3.\n");
        if (is_dvb_s2) {
            MP_ERR(priv, "ERROR: Can not tune to S2 channel, S2-API not "
                         "available, will tune to DVB-S!\n");
        }
        if (ioctl(fd_frontend, FE_SET_FRONTEND, &feparams) < 0) {
            MP_ERR(priv, "ERROR tuning channel\n");
            return -1;
        }
#endif
        break;
    case FE_QAM:
        feparams.frequency = freq;
        feparams.inversion = specInv;
        feparams.u.qam.symbol_rate = srate;
        feparams.u.qam.fec_inner = HP_CodeRate;
        feparams.u.qam.modulation = modulation;
        MP_VERBOSE(priv, "tuning DVB-C to %d, srate=%d\n", freq, srate);
        if (ioctl(fd_frontend, FE_SET_FRONTEND, &feparams) < 0) {
            MP_ERR(priv, "ERROR tuning channel\n");
            return -1;
        }
        break;
#ifdef DVB_ATSC
    case FE_ATSC:
        feparams.frequency = freq;
        feparams.u.vsb.modulation = modulation;
        MP_VERBOSE(priv, "tuning ATSC to %d, modulation=%d\n", freq, modulation);
        if (ioctl(fd_frontend, FE_SET_FRONTEND, &feparams) < 0) {
            MP_ERR(priv, "ERROR tuning channel\n");
            return -1;
        }
        break;
#endif
    default:
        MP_VERBOSE(priv, "Unknown FE type. Aborting\n");
        return 0;
    }
