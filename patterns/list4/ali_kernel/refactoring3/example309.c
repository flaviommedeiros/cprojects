switch (cmd) {
	case SIOCGIWNAME:
		strcpy(wrq->u.name, "IEEE 802.11-DS");
		break;
	case SIOCGIWAP:
		err = usbdrvwext_giwap(dev, NULL, &wrq->u.ap_addr, NULL);
		break;
	case SIOCSIWAP:
		err = usbdrvwext_siwap(dev, NULL, &wrq->u.ap_addr, NULL);
		break;
	case SIOCGIWMODE:
		err = usbdrvwext_giwmode(dev, NULL, &wrq->u.mode, NULL);
		break;
	case SIOCSIWESSID:
		printk(KERN_ERR "CWY - usbdrvwext_siwessid\n");
		/* err = usbdrv_ioctl_setessid(dev, &wrq->u.essid); */
		err = usbdrvwext_siwessid(dev, NULL, &wrq->u.essid, NULL);

		if (!err)
			changed = 1;
		break;
	case SIOCGIWESSID:
		err = usbdrvwext_giwessid(dev, NULL, &wrq->u.essid, NULL);
		break;
	case SIOCSIWRTS:
		err = usbdrv_ioctl_setrts(dev, &wrq->u.rts);
		if (! err)
			changed = 1;
		break;
	/* set_auth */
	case SIOCIWFIRSTPRIV + 0x2: {
		/* printk("CWY - SIOCIWFIRSTPRIV + 0x2(set_auth)\n"); */
		if (!capable(CAP_NET_ADMIN)) {
			err = -EPERM;
			break;
		}
		val = *((int *) wrq->u.name);
		if ((val < 0) || (val > 2)) {
			err = -EINVAL;
			break;
		} else {
			zfiWlanSetAuthenticationMode(dev, val);

			if (macp->DeviceOpened == 1) {
				zfiWlanDisable(dev, 0);
				zfiWlanEnable(dev);
			}

			err = 0;
			changed = 1;
		}
	}
		break;
	/* get_auth */
	case SIOCIWFIRSTPRIV + 0x3: {
		int AuthMode = ZM_AUTH_MODE_OPEN;

		/* printk("CWY - SIOCIWFIRSTPRIV + 0x3(get_auth)\n"); */

		if (wrq->u.data.pointer) {
			wrq->u.data.flags = 1;

			AuthMode = zfiWlanQueryAuthenticationMode(dev, 0);
			if (AuthMode == ZM_AUTH_MODE_OPEN) {
				wrq->u.data.length = 12;

				if (copy_to_user(wrq->u.data.pointer,
					"open system", 12)) {
						return -EFAULT;
				}
			} else if (AuthMode == ZM_AUTH_MODE_SHARED_KEY)	{
				wrq->u.data.length = 11;

				if (copy_to_user(wrq->u.data.pointer,
					"shared key", 11)) {
							return -EFAULT;
				}
			} else if (AuthMode == ZM_AUTH_MODE_AUTO) {
				wrq->u.data.length = 10;

				if (copy_to_user(wrq->u.data.pointer,
					"auto mode", 10)) {
							return -EFAULT;
				}
			} else {
				return -EFAULT;
			}
		}
	}
		break;
	/* debug command */
	case ZDAPIOCTL:
		if (copy_from_user(&zdreq, ifr->ifr_data, sizeof(zdreq))) {
			printk(KERN_ERR "usbdrv : copy_from_user error\n");
			return -EFAULT;
		}

		/* printk(KERN_WARNING
		* "usbdrv : cmd = % 2x, reg = 0x%04lx,
		*value = 0x%08lx\n",
		* zdreq.cmd, zdreq.addr, zdreq.value);
		*/
		zfLnxPrivateIoctl(dev, &zdreq);

		err = 0;
		break;
	case ZD_IOCTL_WPA:
		if (copy_from_user(&zdparm, ifr->ifr_data,
			sizeof(struct athr_wlan_param))) {
			printk(KERN_ERR "usbdrv : copy_from_user error\n");
			return -EFAULT;
		}

		usbdrv_wpa_ioctl(dev, &zdparm);
		err = 0;
		break;
	case ZD_IOCTL_PARAM: {
		int *p;
		int op;
		int arg;

		/* Point to the name field and retrieve the
		* op and arg elements.
		*/
		p = (int *)wrq->u.name;
		op = *p++;
		arg = *p;

		if (op == ZD_PARAM_ROAMING) {
			printk(KERN_ERR
			"*************ZD_PARAM_ROAMING : % d\n", arg);
			/* macp->cardSetting.ap_scan=(U8)arg; */
		}
		if (op == ZD_PARAM_PRIVACY) {
			printk(KERN_ERR "ZD_IOCTL_PRIVACY : ");

			/* Turn on the privacy invoke flag */
			if (arg) {
				/* mCap[0] |= CAP_PRIVACY; */
				/* macp->cardSetting.EncryOnOff[0] = 1; */
				printk(KERN_ERR "enable\n");

			} else {
				/* mCap[0] &= ~CAP_PRIVACY; */
				/* macp->cardSetting.EncryOnOff[0] = 0; */
				printk(KERN_ERR "disable\n");
			}
			/* changed=1; */
		}
		if (op == ZD_PARAM_WPA) {

		printk(KERN_ERR "ZD_PARAM_WPA : ");

		if (arg) {
			printk(KERN_ERR "enable\n");

			if (zfiWlanQueryWlanMode(dev) != ZM_MODE_AP) {
				printk(KERN_ERR "Station Mode\n");
				/* zfiWlanQueryWpaIe(dev, (u8_t *)
					&wpaIe, &wpalen); */
				/* printk("wpaIe : % 2x, % 2x, % 2x\n",
					wpaIe[21], wpaIe[22], wpaIe[23]); */
				/* printk("rsnIe : % 2x, % 2x, % 2x\n",
					wpaIe[17], wpaIe[18], wpaIe[19]); */
				if ((macp->supIe[21] == 0x50) &&
					(macp->supIe[22] == 0xf2) &&
					(macp->supIe[23] == 0x2)) {
					printk(KERN_ERR
				"wd->sta.authMode = ZM_AUTH_MODE_WPAPSK\n");
				/* wd->sta.authMode = ZM_AUTH_MODE_WPAPSK; */
				/* wd->ws.authMode = ZM_AUTH_MODE_WPAPSK; */
				zfiWlanSetAuthenticationMode(dev,
							ZM_AUTH_MODE_WPAPSK);
				} else if ((macp->supIe[21] == 0x50) &&
					(macp->supIe[22] == 0xf2) &&
					(macp->supIe[23] == 0x1)) {
					printk(KERN_ERR
				"wd->sta.authMode = ZM_AUTH_MODE_WPA\n");
				/* wd->sta.authMode = ZM_AUTH_MODE_WPA; */
				/* wd->ws.authMode = ZM_AUTH_MODE_WPA; */
				zfiWlanSetAuthenticationMode(dev,
							ZM_AUTH_MODE_WPA);
					} else if ((macp->supIe[17] == 0xf) &&
						(macp->supIe[18] == 0xac) &&
						(macp->supIe[19] == 0x2))
					{
						printk(KERN_ERR
				"wd->sta.authMode = ZM_AUTH_MODE_WPA2PSK\n");
				/* wd->sta.authMode = ZM_AUTH_MODE_WPA2PSK; */
				/* wd->ws.authMode = ZM_AUTH_MODE_WPA2PSK; */
				zfiWlanSetAuthenticationMode(dev,
				ZM_AUTH_MODE_WPA2PSK);
			} else if ((macp->supIe[17] == 0xf) &&
				(macp->supIe[18] == 0xac) &&
				(macp->supIe[19] == 0x1))
				{
					printk(KERN_ERR
				"wd->sta.authMode = ZM_AUTH_MODE_WPA2\n");
				/* wd->sta.authMode = ZM_AUTH_MODE_WPA2; */
				/* wd->ws.authMode = ZM_AUTH_MODE_WPA2; */
				zfiWlanSetAuthenticationMode(dev,
							ZM_AUTH_MODE_WPA2);
			}
			/* WPA or WPAPSK */
			if ((macp->supIe[21] == 0x50) ||
				(macp->supIe[22] == 0xf2)) {
				if (macp->supIe[11] == 0x2) {
					printk(KERN_ERR
				"wd->sta.wepStatus = ZM_ENCRYPTION_TKIP\n");
				/* wd->sta.wepStatus = ZM_ENCRYPTION_TKIP; */
				/* wd->ws.wepStatus = ZM_ENCRYPTION_TKIP; */
				zfiWlanSetWepStatus(dev, ZM_ENCRYPTION_TKIP);
			} else {
				printk(KERN_ERR
				"wd->sta.wepStatus = ZM_ENCRYPTION_AES\n");
				/* wd->sta.wepStatus = ZM_ENCRYPTION_AES; */
				/* wd->ws.wepStatus = ZM_ENCRYPTION_AES; */
				zfiWlanSetWepStatus(dev, ZM_ENCRYPTION_AES);
				}
			}
			//WPA2 or WPA2PSK
			if ((macp->supIe[17] == 0xf) ||
				(macp->supIe[18] == 0xac)) {
				if (macp->supIe[13] == 0x2) {
					printk(KERN_ERR
				"wd->sta.wepStatus = ZM_ENCRYPTION_TKIP\n");
				/* wd->sta.wepStatus = ZM_ENCRYPTION_TKIP; */
				/* wd->ws.wepStatus = ZM_ENCRYPTION_TKIP; */
				zfiWlanSetWepStatus(dev, ZM_ENCRYPTION_TKIP);
				} else {
					printk(KERN_ERR
				"wd->sta.wepStatus = ZM_ENCRYPTION_AES\n");
				/* wd->sta.wepStatus = ZM_ENCRYPTION_AES; */
				/* wd->ws.wepStatus = ZM_ENCRYPTION_AES; */
				zfiWlanSetWepStatus(dev, ZM_ENCRYPTION_AES);
					}
				}
			}
			zfiWlanSetWpaSupport(dev, 1);
		} else {
			/* Reset the WPA related variables */
			printk(KERN_ERR "disable\n");

			zfiWlanSetWpaSupport(dev, 0);
			zfiWlanSetAuthenticationMode(dev, ZM_AUTH_MODE_OPEN);
			zfiWlanSetWepStatus(dev, ZM_ENCRYPTION_WEP_DISABLED);

			/* Now we only set the length in the WPA IE
			* field to zero.
			*macp->cardSetting.WPAIe[1] = 0;
			*/
			}
		}

		if (op == ZD_PARAM_COUNTERMEASURES) {
			printk(KERN_ERR
				"****************ZD_PARAM_COUNTERMEASURES : ");

			if(arg) {
				/*    mCounterMeasureState=1; */
				printk(KERN_ERR "enable\n");
			} else {
				/*    mCounterMeasureState=0; */
				printk(KERN_ERR "disable\n");
			}
		}
		if (op == ZD_PARAM_DROPUNENCRYPTED) {
			printk(KERN_ERR "ZD_PARAM_DROPUNENCRYPTED : ");

			if(arg) {
				printk(KERN_ERR "enable\n");
			} else {
				printk(KERN_ERR "disable\n");
			}
		}
		if (op == ZD_PARAM_AUTH_ALGS) {
			printk(KERN_ERR "ZD_PARAM_AUTH_ALGS : ");

			if (arg == 0) {
				printk(KERN_ERR "OPEN_SYSTEM\n");
			} else {
				printk(KERN_ERR "SHARED_KEY\n");
			}
		}
		if (op == ZD_PARAM_WPS_FILTER) {
			printk(KERN_ERR "ZD_PARAM_WPS_FILTER : ");

			if (arg) {
				/*    mCounterMeasureState=1; */
				macp->forwardMgmt = 1;
				printk(KERN_ERR "enable\n");
			} else {
				/*    mCounterMeasureState=0; */
				macp->forwardMgmt = 0;
				printk(KERN_ERR "disable\n");
			}
		}
	}
		err = 0;
		break;
	case ZD_IOCTL_GETWPAIE: {
		struct ieee80211req_wpaie req_wpaie;
		u16_t apId, i, j;

		/* Get the AP Id */
		apId = zfLnxGetVapId(dev);

		if (apId == 0xffff) {
			apId = 0;
		} else {
			apId = apId + 1;
		}

		if (copy_from_user(&req_wpaie, ifr->ifr_data,
					sizeof(struct ieee80211req_wpaie))) {
			printk(KERN_ERR "usbdrv : copy_from_user error\n");
			return -EFAULT;
		}

		for (i = 0; i < ZM_OAL_MAX_STA_SUPPORT; i++) {
			for (j = 0; j < IEEE80211_ADDR_LEN; j++) {
				if (macp->stawpaie[i].wpa_macaddr[j] !=
						req_wpaie.wpa_macaddr[j])
				break;
			}
			if (j == 6)
			break;
		}

		if (i < ZM_OAL_MAX_STA_SUPPORT) {
		/* printk("ZD_IOCTL_GETWPAIE - sta index = % d\n", i); */
		memcpy(req_wpaie.wpa_ie, macp->stawpaie[i].wpa_ie,
							IEEE80211_MAX_IE_SIZE);
		}

		if (copy_to_user(wrq->u.data.pointer, &req_wpaie,
				sizeof(struct ieee80211req_wpaie))) {
			return -EFAULT;
		}
	}

		err = 0;
		break;
	#ifdef ZM_ENABLE_CENC
	case ZM_IOCTL_CENC:
		if (copy_from_user(&macp->zd_wpa_req, ifr->ifr_data,
			sizeof(struct athr_wlan_param))) {
			printk(KERN_ERR "usbdrv : copy_from_user error\n");
			return -EFAULT;
		}

		usbdrv_cenc_ioctl(dev,
				(struct zydas_cenc_param *)&macp->zd_wpa_req);
		err = 0;
		break;
	#endif /* ZM_ENABLE_CENC */
	default:
		err = -EOPNOTSUPP;
		break;
	}
