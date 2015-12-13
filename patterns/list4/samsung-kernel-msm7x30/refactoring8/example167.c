const tRfChannelProps rfChannels[NUM_RF_CHANNELS] =
{
    //RF_SUBBAND_2_4_GHZ
    //freq, chan#, band
    { 2412, 1  , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_1,
    { 2417, 2  , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_2,
    { 2422, 3  , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_3,
    { 2427, 4  , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_4,
    { 2432, 5  , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_5,
    { 2437, 6  , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_6,
    { 2442, 7  , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_7,
    { 2447, 8  , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_8,
    { 2452, 9  , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_9,
    { 2457, 10 , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_10,
    { 2462, 11 , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_11,
    { 2467, 12 , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_12,
    { 2472, 13 , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_13,
    { 2484, 14 , RF_SUBBAND_2_4_GHZ},        //RF_CHAN_14,
#ifdef FEATURE_WLAN_INTEGRATED_SOC
    { 0,    240, RF_SUBBAND_4_9_GHZ},        //RF_CHAN_240,
    { 0,    244, RF_SUBBAND_4_9_GHZ},        //RF_CHAN_244,
    { 0,    248, RF_SUBBAND_4_9_GHZ},        //RF_CHAN_248,
    { 0,    252, RF_SUBBAND_4_9_GHZ},        //RF_CHAN_252,
    { 0,    208, RF_SUBBAND_4_9_GHZ},        //RF_CHAN_208,
    { 0,    212, RF_SUBBAND_4_9_GHZ},        //RF_CHAN_212,
    { 0,    216, RF_SUBBAND_4_9_GHZ},        //RF_CHAN_216,
    { 5180, 36 , RF_SUBBAND_5_LOW_GHZ},      //RF_CHAN_36,
    { 5200, 40 , RF_SUBBAND_5_LOW_GHZ},      //RF_CHAN_40,
    { 5220, 44 , RF_SUBBAND_5_LOW_GHZ},      //RF_CHAN_44,
    { 5240, 48 , RF_SUBBAND_5_LOW_GHZ},      //RF_CHAN_48,
    { 5260, 52 , RF_SUBBAND_5_LOW_GHZ},      //RF_CHAN_52,
    { 5280, 56 , RF_SUBBAND_5_LOW_GHZ},      //RF_CHAN_56,
    { 5300, 60 , RF_SUBBAND_5_LOW_GHZ},      //RF_CHAN_60,
    { 5320, 64 , RF_SUBBAND_5_LOW_GHZ},      //RF_CHAN_64,
    { 5500, 100, RF_SUBBAND_5_MID_GHZ},      //RF_CHAN_100,
    { 5520, 104, RF_SUBBAND_5_MID_GHZ},      //RF_CHAN_104,
    { 5540, 108, RF_SUBBAND_5_MID_GHZ},      //RF_CHAN_108,
    { 5560, 112, RF_SUBBAND_5_MID_GHZ},      //RF_CHAN_112,
    { 5580, 116, RF_SUBBAND_5_MID_GHZ},      //RF_CHAN_116,
    { 5600, 120, RF_SUBBAND_5_MID_GHZ},      //RF_CHAN_120,
    { 5620, 124, RF_SUBBAND_5_MID_GHZ},      //RF_CHAN_124,
    { 5640, 128, RF_SUBBAND_5_MID_GHZ},      //RF_CHAN_128,
    { 5660, 132, RF_SUBBAND_5_MID_GHZ},      //RF_CHAN_132,
    { 5680, 136, RF_SUBBAND_5_MID_GHZ},      //RF_CHAN_136,
    { 5700, 140, RF_SUBBAND_5_MID_GHZ},      //RF_CHAN_140,
    { 5745, 149, RF_SUBBAND_5_HIGH_GHZ},     //RF_CHAN_149,
    { 5765, 153, RF_SUBBAND_5_HIGH_GHZ},     //RF_CHAN_153,
    { 5785, 157, RF_SUBBAND_5_HIGH_GHZ},     //RF_CHAN_157,
    { 5805, 161, RF_SUBBAND_5_HIGH_GHZ},     //RF_CHAN_161,
    { 5825, 165, RF_SUBBAND_5_HIGH_GHZ},     //RF_CHAN_165,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_3,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_4,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_5,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_6,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_7,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_8,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_9,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_10,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_11,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_242,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_246,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_250,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_210,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_214,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_38,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_42,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_46,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_50,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_54,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_58,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_62,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_102,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_106,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_110,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_114,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_118,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_122,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_126,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_130,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_134,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_138,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_151,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_155,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_159,
    { 0   , 0  , NUM_RF_SUBBANDS},           //RF_CHAN_BOND_163,
#endif
};