#ifdef WLANDXE_TEST_CHANNEL_ENABLE
if((WDTS_CHANNEL_RX_LOW_PRI  == channelEntry->channelType) ||
         (WDTS_CHANNEL_RX_HIGH_PRI == channelEntry->channelType) ||
         (WDTS_CHANNEL_H2H_TEST_RX == channelEntry->channelType))
#else
      if((WDTS_CHANNEL_RX_LOW_PRI  == channelEntry->channelType) ||
         (WDTS_CHANNEL_RX_HIGH_PRI == channelEntry->channelType))
#endif /* WLANDXE_TEST_CHANNEL_ENABLE */
      {
         status = dxeRXFrameSingleBufferAlloc(dxeCtrlBlk,
                                              channelEntry,
                                              currentCtrlBlk);
         if( !WLAN_PAL_IS_STATUS_SUCCESS(status) )
         {
            HDXE_MSG(eWLAN_MODULE_DAL_DATA, eWLAN_PAL_TRACE_LEVEL_ERROR,
                     "dxeDescLinkAlloc RX Buffer Alloc Fail for channel %d",
                     channelEntry->channelType);
            return status;
         }
         --channelEntry->numFreeDesc;
      }
