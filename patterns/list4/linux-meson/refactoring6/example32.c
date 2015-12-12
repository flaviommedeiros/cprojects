if ((pattrib->ether_type != 0x888e) &&
			(pattrib->ether_type != 0x0806) &&
			(pattrib->ether_type != 0x88B4) &&
			(pattrib->dhcp_pkt != 1) &&
			(drv_userate != 1)
#ifdef CONFIG_AUTO_AP_MODE
		    && (pattrib->pctrl != _TRUE)
#endif
			)
		{
			// Non EAP & ARP & DHCP type data packet

			if (pattrib->ampdu_en == _TRUE) {
				SET_TX_DESC_AGG_ENABLE_8723B(pbuf, 1);
				SET_TX_DESC_MAX_AGG_NUM_8723B(pbuf, 0x1F);
				SET_TX_DESC_AMPDU_DENSITY_8723B(pbuf, pattrib->ampdu_spacing);
			}
			else {
				SET_TX_DESC_AGG_BREAK_8723B(pbuf, 1);
			}

			fill_txdesc_phy_8723b(padapter, pattrib, pbuf);

			SET_TX_DESC_DATA_RATE_FB_LIMIT_8723B(pbuf, 0x1F);

			if (pHalData->fw_ractrl == _FALSE) {
				SET_TX_DESC_USE_RATE_8723B(pbuf, 1);

				if (pHalData->INIDATA_RATE[pattrib->mac_id] & BIT(7)) {
					SET_TX_DESC_DATA_SHORT_8723B(pbuf, 1);
				}

				SET_TX_DESC_TX_RATE_8723B(pbuf, pHalData->INIDATA_RATE[pattrib->mac_id] & 0x7F);
			}

			// modify data rate by iwpriv
			if (padapter->fix_rate != 0xFF) {
				SET_TX_DESC_USE_RATE_8723B(pbuf, 1);
				if (padapter->fix_rate & BIT(7)) {
					SET_TX_DESC_DATA_SHORT_8723B(pbuf, 1);
				}
				SET_TX_DESC_TX_RATE_8723B(pbuf, padapter->fix_rate & 0x7F);
				if (!padapter->data_fb) {
					SET_TX_DESC_DISABLE_FB_8723B(pbuf, 1);
				}
			}

			if (pattrib->ldpc) {
				SET_TX_DESC_DATA_LDPC_8723B(pbuf, 1);
			}

			if (pattrib->stbc) {
				SET_TX_DESC_DATA_STBC_8723B(pbuf, 1);
			}

#ifdef CONFIG_CMCC_TEST
			SET_TX_DESC_DATA_SHORT_8723B(pbuf, 1); /* use cck short premble */
#endif
		}
		else
		{
			// EAP data packet and ARP packet.
			// Use the 1M data rate to send the EAP/ARP packet.
			// This will maybe make the handshake smooth.

			SET_TX_DESC_AGG_BREAK_8723B(pbuf, 1);
			SET_TX_DESC_USE_RATE_8723B(pbuf, 1);
			if (pmlmeinfo->preamble_mode == PREAMBLE_SHORT) {
				SET_TX_DESC_DATA_SHORT_8723B(pbuf, 1);
			}
			SET_TX_DESC_TX_RATE_8723B(pbuf, MRateToHwRate(pmlmeext->tx_rate));

			DBG_8192C(FUNC_ADPT_FMT ": SP Packet(0x%04X) rate=0x%x\n",
				FUNC_ADPT_ARG(padapter), pattrib->ether_type, MRateToHwRate(pmlmeext->tx_rate));
		}
