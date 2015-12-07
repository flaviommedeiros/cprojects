#ifdef CONFIG_SH_HICOSH4
if (1) {
		/* For the HiCO.SH4 board, things are different: we don't
		   have EEPROM, but there is some data in flash, so we go
		   get it there directly (MAC). */
		__u16 *confd;
		short cnt;
		if (((* (volatile __u32 *) 0xa0013ff0) & 0x00ffffff)
			== 0x006c3000) {
			confd = (__u16*) 0xa0013fc0;
		} else {
			confd = (__u16*) 0xa001ffc0;
		}
		cnt = (*confd++ & 0x00ff) >> 1;
		while (--cnt > 0) {
			__u16 j = *confd++;

			switch (j & 0x0fff) {
			case PP_IA:
				for (i = 0; i < ETH_ALEN/2; i++) {
					dev->dev_addr[i*2] = confd[i] & 0xFF;
					dev->dev_addr[i*2+1] = confd[i] >> 8;
				}
				break;
			}
			j = (j >> 12) + 1;
			confd += j;
			cnt -= j;
		}
	} else
#endif

        if ((readreg(dev, PP_SelfST) & (EEPROM_OK | EEPROM_PRESENT)) ==
	      (EEPROM_OK|EEPROM_PRESENT)) {
	        /* Load the MAC. */
		for (i=0; i < ETH_ALEN/2; i++) {
	                unsigned int Addr;
			Addr = readreg(dev, PP_IA+i*2);
		        dev->dev_addr[i*2] = Addr & 0xFF;
		        dev->dev_addr[i*2+1] = Addr >> 8;
		}

	   	/* Load the Adapter Configuration.
		   Note:  Barring any more specific information from some
		   other source (ie EEPROM+Schematics), we would not know
		   how to operate a 10Base2 interface on the AUI port.
		   However, since we  do read the status of HCB1 and use
		   settings that always result in calls to control_dc_dc(dev,0)
		   a BNC interface should work if the enable pin
		   (dc/dc converter) is on HCB1. It will be called AUI
		   however. */

		lp->adapter_cnf = 0;
		i = readreg(dev, PP_LineCTL);
		/* Preserve the setting of the HCB1 pin. */
		if ((i & (HCB1 | HCB1_ENBL)) ==  (HCB1 | HCB1_ENBL))
			lp->adapter_cnf |= A_CNF_DC_DC_POLARITY;
		/* Save the sqelch bit */
		if ((i & LOW_RX_SQUELCH) == LOW_RX_SQUELCH)
			lp->adapter_cnf |= A_CNF_EXTND_10B_2 | A_CNF_LOW_RX_SQUELCH;
		/* Check if the card is in 10Base-t only mode */
		if ((i & (AUI_ONLY | AUTO_AUI_10BASET)) == 0)
			lp->adapter_cnf |=  A_CNF_10B_T | A_CNF_MEDIA_10B_T;
		/* Check if the card is in AUI only mode */
		if ((i & (AUI_ONLY | AUTO_AUI_10BASET)) == AUI_ONLY)
			lp->adapter_cnf |=  A_CNF_AUI | A_CNF_MEDIA_AUI;
		/* Check if the card is in Auto mode. */
		if ((i & (AUI_ONLY | AUTO_AUI_10BASET)) == AUTO_AUI_10BASET)
			lp->adapter_cnf |=  A_CNF_AUI | A_CNF_10B_T |
			A_CNF_MEDIA_AUI | A_CNF_MEDIA_10B_T | A_CNF_MEDIA_AUTO;

		if (net_debug > 1)
			printk(KERN_INFO "%s: PP_LineCTL=0x%x, adapter_cnf=0x%x\n",
					dev->name, i, lp->adapter_cnf);

		/* IRQ. Other chips already probe, see below. */
		if (lp->chip_type == CS8900)
			lp->isa_config = readreg(dev, PP_CS8900_ISAINT) & INT_NO_MASK;

		printk( "[Cirrus EEPROM] ");
	}
