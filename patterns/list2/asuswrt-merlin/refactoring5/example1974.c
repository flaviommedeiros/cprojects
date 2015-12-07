#ifdef CONFIG_8139TOO_8129
if (tp->drv_flags & HAS_MII_XCVR) {
		int phy, phy_idx = 0;
		for (phy = 0; phy < 32 && phy_idx < sizeof(tp->phys); phy++) {
			int mii_status = mdio_read(dev, phy, 1);
			if (mii_status != 0xffff  &&  mii_status != 0x0000) {
				u16 advertising = mdio_read(dev, phy, 4);
				tp->phys[phy_idx++] = phy;
				netdev_info(dev, "MII transceiver %d status 0x%04x advertising %04x\n",
					    phy, mii_status, advertising);
			}
		}
		if (phy_idx == 0) {
			netdev_info(dev, "No MII transceivers found! Assuming SYM transceiver\n");
			tp->phys[0] = 32;
		}
	} else
#endif
		tp->phys[0] = 32;
