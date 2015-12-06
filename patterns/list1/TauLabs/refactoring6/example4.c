if (!(rdes->rdes0 & (STM32_RDES0_AFM | STM32_RDES0_ES))
#if STM32_MAC_IP_CHECKSUM_OFFLOAD
        && (rdes->rdes0 & STM32_RDES0_FT)
        && !(rdes->rdes0 & (STM32_RDES0_IPHCE | STM32_RDES0_PCE))
#endif
        && (rdes->rdes0 & STM32_RDES0_FS) && (rdes->rdes0 & STM32_RDES0_LS)) {
      /* Found a valid one.*/
      rdp->offset   = 0;
      rdp->size     = ((rdes->rdes0 & STM32_RDES0_FL_MASK) >> 16) - 4;
      rdp->physdesc = rdes;
      macp->rxptr   = (stm32_eth_rx_descriptor_t *)rdes->rdes3;

      chSysUnlock();
      return RDY_OK;
    }
