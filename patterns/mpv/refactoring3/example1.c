switch (fe_info.type) {
    case FE_OFDM:
        mp_verbose(log, "TUNER TYPE SEEMS TO BE DVB-T\n");
        return TUNER_TER;

    case FE_QPSK:
        mp_verbose(log, "TUNER TYPE SEEMS TO BE DVB-S\n");
        return TUNER_SAT;

    case FE_QAM:
        mp_verbose(log, "TUNER TYPE SEEMS TO BE DVB-C\n");
        return TUNER_CBL;

#ifdef DVB_ATSC
    case FE_ATSC:
        mp_verbose(log, "TUNER TYPE SEEMS TO BE DVB-ATSC\n");
        return TUNER_ATSC;
#endif
    default:
        mp_err(log, "UNKNOWN TUNER TYPE\n");
        return 0;
    }
