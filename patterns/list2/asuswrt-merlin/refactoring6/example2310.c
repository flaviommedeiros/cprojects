if (
#ifdef IW_WIRELESS_SPY		/* defined in iw_handler.h */
		   (lp->spy_data.spy_number > 0) ||
#endif /* IW_WIRELESS_SPY */
#ifdef HISTOGRAM
		   (lp->his_number > 0) ||
#endif /* HISTOGRAM */
		   0) {
		u8 stats[3];	/* signal level, noise level, signal quality */

		/* Read signal level, silence level and signal quality bytes */
		/* Note: in the PCMCIA hardware, these are part of the frame.
		 * It seems that for the ISA hardware, it's nowhere to be
		 * found in the frame, so I'm obliged to do this (it has a
		 * side effect on /proc/net/wireless).
		 * Any ideas?
		 */
		mmc_out(ioaddr, mmwoff(0, mmw_freeze), 1);
		mmc_read(ioaddr, mmroff(0, mmr_signal_lvl), stats, 3);
		mmc_out(ioaddr, mmwoff(0, mmw_freeze), 0);

#ifdef DEBUG_RX_INFO
		printk(KERN_DEBUG
		       "%s: wv_packet_read(): Signal level %d/63, Silence level %d/63, signal quality %d/16\n",
		       dev->name, stats[0] & 0x3F, stats[1] & 0x3F,
		       stats[2] & 0x0F);
#endif

		/* Spying stuff */
#ifdef IW_WIRELESS_SPY
		wl_spy_gather(dev, skb_mac_header(skb) + WAVELAN_ADDR_SIZE,
			      stats);
#endif /* IW_WIRELESS_SPY */
#ifdef HISTOGRAM
		wl_his_gather(dev, stats);
#endif /* HISTOGRAM */
	}
