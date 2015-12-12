switch (hw->fc.requested_mode) {
	case ixgbe_fc_none:
		/* Flow control completely disabled by software override. */
		reg &= ~(IXGBE_PCS1GANA_SYM_PAUSE | IXGBE_PCS1GANA_ASM_PAUSE);
		if (hw->phy.media_type == ixgbe_media_type_backplane)
			reg_bp &= ~(IXGBE_AUTOC_SYM_PAUSE |
				    IXGBE_AUTOC_ASM_PAUSE);
		else if (hw->phy.media_type == ixgbe_media_type_copper)
			reg_cu &= ~(IXGBE_TAF_SYM_PAUSE | IXGBE_TAF_ASM_PAUSE);
		break;
	case ixgbe_fc_rx_pause:
		/*
		 * Rx Flow control is enabled and Tx Flow control is
		 * disabled by software override. Since there really
		 * isn't a way to advertise that we are capable of RX
		 * Pause ONLY, we will advertise that we support both
		 * symmetric and asymmetric Rx PAUSE.  Later, we will
		 * disable the adapter's ability to send PAUSE frames.
		 */
		reg |= (IXGBE_PCS1GANA_SYM_PAUSE | IXGBE_PCS1GANA_ASM_PAUSE);
		if (hw->phy.media_type == ixgbe_media_type_backplane)
			reg_bp |= (IXGBE_AUTOC_SYM_PAUSE |
				   IXGBE_AUTOC_ASM_PAUSE);
		else if (hw->phy.media_type == ixgbe_media_type_copper)
			reg_cu |= (IXGBE_TAF_SYM_PAUSE | IXGBE_TAF_ASM_PAUSE);
		break;
	case ixgbe_fc_tx_pause:
		/*
		 * Tx Flow control is enabled, and Rx Flow control is
		 * disabled by software override.
		 */
		reg |= (IXGBE_PCS1GANA_ASM_PAUSE);
		reg &= ~(IXGBE_PCS1GANA_SYM_PAUSE);
		if (hw->phy.media_type == ixgbe_media_type_backplane) {
			reg_bp |= (IXGBE_AUTOC_ASM_PAUSE);
			reg_bp &= ~(IXGBE_AUTOC_SYM_PAUSE);
		} else if (hw->phy.media_type == ixgbe_media_type_copper) {
			reg_cu |= (IXGBE_TAF_ASM_PAUSE);
			reg_cu &= ~(IXGBE_TAF_SYM_PAUSE);
		}
		break;
	case ixgbe_fc_full:
		/* Flow control (both Rx and Tx) is enabled by SW override. */
		reg |= (IXGBE_PCS1GANA_SYM_PAUSE | IXGBE_PCS1GANA_ASM_PAUSE);
		if (hw->phy.media_type == ixgbe_media_type_backplane)
			reg_bp |= (IXGBE_AUTOC_SYM_PAUSE |
				   IXGBE_AUTOC_ASM_PAUSE);
		else if (hw->phy.media_type == ixgbe_media_type_copper)
			reg_cu |= (IXGBE_TAF_SYM_PAUSE | IXGBE_TAF_ASM_PAUSE);
		break;
#ifdef CONFIG_DCB
	case ixgbe_fc_pfc:
		goto out;
		break;
#endif /* CONFIG_DCB */
	default:
		hw_dbg(hw, "Flow control param set incorrectly\n");
		ret_val = IXGBE_ERR_CONFIG;
		goto out;
		break;
	}
