static const AVOption fdk_aac_dec_options[] = {
    { "conceal", "Error concealment method", OFFSET(conceal_method), AV_OPT_TYPE_INT, { .i64 = CONCEAL_METHOD_NOISE_SUBSTITUTION }, CONCEAL_METHOD_SPECTRAL_MUTING, CONCEAL_METHOD_NB - 1, AD, "conceal" },
    { "spectral", "Spectral muting",      0, AV_OPT_TYPE_CONST, { .i64 = CONCEAL_METHOD_SPECTRAL_MUTING },      INT_MIN, INT_MAX, AD, "conceal" },
    { "noise",    "Noise Substitution",   0, AV_OPT_TYPE_CONST, { .i64 = CONCEAL_METHOD_NOISE_SUBSTITUTION },   INT_MIN, INT_MAX, AD, "conceal" },
    { "energy",   "Energy Interpolation", 0, AV_OPT_TYPE_CONST, { .i64 = CONCEAL_METHOD_ENERGY_INTERPOLATION }, INT_MIN, INT_MAX, AD, "conceal" },
    { "drc_boost", "Dynamic Range Control: boost, where [0] is none and [127] is max boost",
                     OFFSET(drc_boost),      AV_OPT_TYPE_INT,   { .i64 = -1 }, -1, 127, AD, NULL    },
    { "drc_cut",   "Dynamic Range Control: attenuation factor, where [0] is none and [127] is max compression",
                     OFFSET(drc_cut),        AV_OPT_TYPE_INT,   { .i64 = -1 }, -1, 127, AD, NULL    },
    { "drc_level", "Dynamic Range Control: reference level, quantized to 0.25dB steps where [0] is 0dB and [127] is -31.75dB",
                     OFFSET(drc_level),      AV_OPT_TYPE_INT,   { .i64 = -1},  -1, 127, AD, NULL    },
    { "drc_heavy", "Dynamic Range Control: heavy compression, where [1] is on (RF mode) and [0] is off",
                     OFFSET(drc_heavy),      AV_OPT_TYPE_INT,   { .i64 = -1},  -1, 1,   AD, NULL    },
#ifdef AACDECODER_LIB_VL0
    { "level_limit", "Signal level limiting", OFFSET(level_limit), AV_OPT_TYPE_INT, { .i64 = 0 }, -1, 1, AD },
#endif
    { NULL }
};
