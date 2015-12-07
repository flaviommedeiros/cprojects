if(
#ifdef IW_WIRELESS_SPY
     (lp->spy_data.spy_number > 0) ||
#endif	/* IW_WIRELESS_SPY */
#ifdef HISTOGRAM
     (lp->his_number > 0) ||
#endif	/* HISTOGRAM */
#ifdef WAVELAN_ROAMING
     (do_roaming) ||
#endif	/* WAVELAN_ROAMING */
     0)
    {
      u_char	stats[3];	/* Signal level, Noise level, Signal quality */

      /* read signal level, silence level and signal quality bytes */
      fd_p = read_ringbuf(dev, (fd_p + 4) % RX_SIZE + RX_BASE,
			  stats, 3);
#ifdef DEBUG_RX_INFO
      printk(KERN_DEBUG "%s: wv_packet_read(): Signal level %d/63, Silence level %d/63, signal quality %d/16\n",
	     dev->name, stats[0] & 0x3F, stats[1] & 0x3F, stats[2] & 0x0F);
#endif

#ifdef WAVELAN_ROAMING
      if(do_roaming)
	if(WAVELAN_BEACON(skb->data))
	  wl_roam_gather(dev, skb->data, stats);
#endif	/* WAVELAN_ROAMING */
	  
#ifdef WIRELESS_SPY
      wl_spy_gather(dev, skb_mac_header(skb) + WAVELAN_ADDR_SIZE, stats);
#endif	/* WIRELESS_SPY */
#ifdef HISTOGRAM
      wl_his_gather(dev, stats);
#endif	/* HISTOGRAM */
    }
