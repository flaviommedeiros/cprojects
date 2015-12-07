if (
#ifdef RT2860
		   (device_id == NIC2860_PCIe_DEVICE_ID) ||
		   (device_id == NIC2790_PCIe_DEVICE_ID) ||
		   (device_id == VEN_AWT_PCIe_DEVICE_ID) ||
#endif
#ifdef RT3090
		   (device_id == NIC3090_PCIe_DEVICE_ID) ||
		   (device_id == NIC3091_PCIe_DEVICE_ID) ||
		   (device_id == NIC3092_PCIe_DEVICE_ID) ||
#endif /* RT3090 // */
		   0) {
		u32 MacCsr0 = 0, Index = 0;
		do {
			RTMP_IO_READ32(pAd, MAC_CSR0, &MacCsr0);

			if ((MacCsr0 != 0x00) && (MacCsr0 != 0xFFFFFFFF))
				break;

			RTMPusecDelay(10);
		} while (Index++ < 100);

		/* Support advanced power save after 2892/2790. */
		/* MAC version at offset 0x1000 is 0x2872XXXX/0x2870XXXX(PCIe, USB, SDIO). */
		if ((MacCsr0 & 0xffff0000) != 0x28600000)
			OPSTATUS_SET_FLAG(pAd, fOP_STATUS_PCIE_DEVICE);
	}
