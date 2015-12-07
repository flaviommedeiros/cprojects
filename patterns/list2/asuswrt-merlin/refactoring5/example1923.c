#ifdef INCLUDE_TCP_SEG_SUPPORT
if (T3_ASIC_REV(pDevice->ChipRevId) == T3_ASIC_REV_5705)
      {
	Wr_fn = LM_MemWrInd;
	Rd_fn = LM_MemRdInd;
	len = LM_GetStkOffLdFirmwareSize(pDevice);
	base_addr = T3_NIC_BCM5705_MBUF_POOL_ADDR;
      }
    else
#endif
      {
	Wr_fn = LM_RegWrInd;
	Rd_fn = LM_RegRdInd;
	len = T3_RX_CPU_SPAD_SIZE;
	base_addr = T3_RX_CPU_SPAD_ADDR;
      }
