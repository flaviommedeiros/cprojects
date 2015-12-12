switch (board_info(adapter)->board) {
#ifdef CONFIG_CHELSIO_T1_1G
	case CHBT_BOARD_CHT204:
	case CHBT_BOARD_CHT204E:
	case CHBT_BOARD_CHN204:
	case CHBT_BOARD_CHT204V: {
		int i, port_bit;
		for_each_port(adapter, i) {
			port_bit = i + 1;
			if (!(cause & (1 << port_bit)))
				continue;

			phy = adapter->port[i].phy;
			phy_cause = phy->ops->interrupt_handler(phy);
			if (phy_cause & cphy_cause_link_change)
				t1_link_changed(adapter, i);
		}
		break;
	}
	case CHBT_BOARD_CHT101:
		if (cause & ELMER0_GP_BIT1) { /* Marvell 88E1111 interrupt */
			phy = adapter->port[0].phy;
			phy_cause = phy->ops->interrupt_handler(phy);
			if (phy_cause & cphy_cause_link_change)
				t1_link_changed(adapter, 0);
		}
		break;
	case CHBT_BOARD_7500: {
		int p;
		/*
		 * Elmer0's interrupt cause isn't useful here because there is
		 * only one bit that can be set for all 4 ports.  This means
		 * we are forced to check every PHY's interrupt status
		 * register to see who initiated the interrupt.
		 */
		for_each_port(adapter, p) {
			phy = adapter->port[p].phy;
			phy_cause = phy->ops->interrupt_handler(phy);
			if (phy_cause & cphy_cause_link_change)
			    t1_link_changed(adapter, p);
		}
		break;
	}
#endif
	case CHBT_BOARD_CHT210:
	case CHBT_BOARD_N210:
	case CHBT_BOARD_N110:
		if (cause & ELMER0_GP_BIT6) { /* Marvell 88x2010 interrupt */
			phy = adapter->port[0].phy;
			phy_cause = phy->ops->interrupt_handler(phy);
			if (phy_cause & cphy_cause_link_change)
				t1_link_changed(adapter, 0);
		}
		break;
	case CHBT_BOARD_8000:
	case CHBT_BOARD_CHT110:
		if (netif_msg_intr(adapter))
			dev_dbg(&adapter->pdev->dev,
				"External interrupt cause 0x%x\n", cause);
		if (cause & ELMER0_GP_BIT1) {        /* PMC3393 INTB */
			struct cmac *mac = adapter->port[0].mac;

			mac->ops->interrupt_handler(mac);
		}
		if (cause & ELMER0_GP_BIT5) {        /* XPAK MOD_DETECT */
			u32 mod_detect;

			t1_tpi_read(adapter,
					A_ELMER0_GPI_STAT, &mod_detect);
			if (netif_msg_link(adapter))
				dev_info(&adapter->pdev->dev, "XPAK %s\n",
					 mod_detect ? "removed" : "inserted");
		}
		break;
	}
