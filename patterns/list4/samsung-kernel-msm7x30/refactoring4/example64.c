#ifdef WLANDXE_TEST_CHANNEL_ENABLE
if((WDTS_CHANNEL_TX_LOW_PRI == channelEntry->channelType) ||
         (WDTS_CHANNEL_TX_HIGH_PRI == channelEntry->channelType) ||
         (WDTS_CHANNEL_H2H_TEST_TX == channelEntry->channelType))
#else
      if((WDTS_CHANNEL_TX_LOW_PRI == channelEntry->channelType) ||
         (WDTS_CHANNEL_TX_HIGH_PRI == channelEntry->channelType))
#endif /* WLANDXE_TEST_CHANNEL_ENABLE */
      {
         interruptPath |= (1 << channelEntry->assignedDMAChannel);
      }
      else if((WDTS_CHANNEL_RX_LOW_PRI == channelEntry->channelType) ||
              (WDTS_CHANNEL_RX_HIGH_PRI == channelEntry->channelType))
      {
         interruptPath |= (1 << (channelEntry->assignedDMAChannel + 16));
      }
      else
      {
         HDXE_MSG(eWLAN_MODULE_DAL_DATA, eWLAN_PAL_TRACE_LEVEL_ERROR,
                  "H2H TEST RX???? %d", channelEntry->channelType);
      }
