static char                   *channelType[WDTS_CHANNEL_MAX] =
   {
      "TX_LOW_PRI",
      "TX_HIGH_PRI",
      "RX_LOW_PRI",
#ifndef WLANDXE_TEST_CHANNEL_ENABLE
      "RX_HIGH_PRI",
#else
      "H2H_TEST_TX",
      "H2H_TEST_RX"
#endif /* WLANDXE_TEST_CHANNEL_ENABLE */
   };
