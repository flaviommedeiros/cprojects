if ((priv->pmib->dot11nConfigEntry.dot11nSTBC) &&
				((pstat->ht_cap_buf.ht_cap_info & cpu_to_le16(_HTCAP_RX_STBC_CAP_))
#ifdef RTK_AC_SUPPORT
				 || (pstat->vht_cap_buf.vht_cap_info & cpu_to_le32(_VHTCAP_RX_STBC_CAP_))
#endif
				))
				stbc_en = 1;
