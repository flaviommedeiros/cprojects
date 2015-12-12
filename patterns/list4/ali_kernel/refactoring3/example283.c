switch(cmd) {

	case SIOCGIWNAME:
		rc = iwctl_giwname(dev, NULL, (char *)&(wrq->u.name), NULL);
		break;

	case SIOCGIWNWID:     //0x8b03  support
	#ifdef  WPA_SUPPLICANT_DRIVER_WEXT_SUPPORT
          rc = iwctl_giwnwid(dev, NULL, &(wrq->u.nwid), NULL);
	#else
        rc = -EOPNOTSUPP;
	#endif
		break;

		// Set frequency/channel
	case SIOCSIWFREQ:
	    rc = iwctl_siwfreq(dev, NULL, &(wrq->u.freq), NULL);
		break;

		// Get frequency/channel
	case SIOCGIWFREQ:
		rc = iwctl_giwfreq(dev, NULL, &(wrq->u.freq), NULL);
		break;

		// Set desired network name (ESSID)
	case SIOCSIWESSID:

		{
			char essid[IW_ESSID_MAX_SIZE+1];
			if (wrq->u.essid.length > IW_ESSID_MAX_SIZE) {
				rc = -E2BIG;
				break;
			}
			if (copy_from_user(essid, wrq->u.essid.pointer,
					   wrq->u.essid.length)) {
				rc = -EFAULT;
				break;
			}
			rc = iwctl_siwessid(dev, NULL,
					    &(wrq->u.essid), essid);
		}
		break;


		// Get current network name (ESSID)
	case SIOCGIWESSID:

		{
			char essid[IW_ESSID_MAX_SIZE+1];
			if (wrq->u.essid.pointer)
				rc = iwctl_giwessid(dev, NULL,
						    &(wrq->u.essid), essid);
				if (copy_to_user(wrq->u.essid.pointer,
						         essid,
						         wrq->u.essid.length) )
					rc = -EFAULT;
		}
		break;

	case SIOCSIWAP:

		rc = iwctl_siwap(dev, NULL, &(wrq->u.ap_addr), NULL);
		break;


		// Get current Access Point (BSSID)
	case SIOCGIWAP:
		rc = iwctl_giwap(dev, NULL, &(wrq->u.ap_addr), NULL);
		break;


		// Set desired station name
	case SIOCSIWNICKN:
        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCSIWNICKN \n");
        rc = -EOPNOTSUPP;
		break;

		// Get current station name
	case SIOCGIWNICKN:
        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCGIWNICKN \n");
        rc = -EOPNOTSUPP;
		break;

		// Set the desired bit-rate
	case SIOCSIWRATE:
		rc = iwctl_siwrate(dev, NULL, &(wrq->u.bitrate), NULL);
		break;

	// Get the current bit-rate
	case SIOCGIWRATE:

		rc = iwctl_giwrate(dev, NULL, &(wrq->u.bitrate), NULL);
		break;

	// Set the desired RTS threshold
	case SIOCSIWRTS:

		rc = iwctl_siwrts(dev, NULL, &(wrq->u.rts), NULL);
		break;

	// Get the current RTS threshold
	case SIOCGIWRTS:

		rc = iwctl_giwrts(dev, NULL, &(wrq->u.rts), NULL);
		break;

		// Set the desired fragmentation threshold
	case SIOCSIWFRAG:

		rc = iwctl_siwfrag(dev, NULL, &(wrq->u.frag), NULL);
	    break;

	// Get the current fragmentation threshold
	case SIOCGIWFRAG:

		rc = iwctl_giwfrag(dev, NULL, &(wrq->u.frag), NULL);
		break;

		// Set mode of operation
	case SIOCSIWMODE:
    	rc = iwctl_siwmode(dev, NULL, &(wrq->u.mode), NULL);
		break;

		// Get mode of operation
	case SIOCGIWMODE:
		rc = iwctl_giwmode(dev, NULL, &(wrq->u.mode), NULL);
		break;

		// Set WEP keys and mode
	case SIOCSIWENCODE:
		{
            char abyKey[WLAN_WEP232_KEYLEN];

			if (wrq->u.encoding.pointer) {


				if (wrq->u.encoding.length > WLAN_WEP232_KEYLEN) {
					rc = -E2BIG;
					break;
				}
				memset(abyKey, 0, WLAN_WEP232_KEYLEN);
				if (copy_from_user(abyKey,
				                  wrq->u.encoding.pointer,
				                  wrq->u.encoding.length)) {
					rc = -EFAULT;
					break;
				}
			} else if (wrq->u.encoding.length != 0) {
				rc = -EINVAL;
				break;
			}
			rc = iwctl_siwencode(dev, NULL, &(wrq->u.encoding), abyKey);
		}
		break;

		// Get the WEP keys and mode
	case SIOCGIWENCODE:

		if (!capable(CAP_NET_ADMIN)) {
			rc = -EPERM;
			break;
		}
		{
		    char abyKey[WLAN_WEP232_KEYLEN];

		    rc = iwctl_giwencode(dev, NULL, &(wrq->u.encoding), abyKey);
		    if (rc != 0) break;
			if (wrq->u.encoding.pointer) {
				if (copy_to_user(wrq->u.encoding.pointer,
						        abyKey,
						        wrq->u.encoding.length))
					rc = -EFAULT;
			}
		}
		break;

		// Get the current Tx-Power
	case SIOCGIWTXPOW:
        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCGIWTXPOW \n");
        rc = -EOPNOTSUPP;
		break;

	case SIOCSIWTXPOW:
        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCGIWTXPOW \n");
        rc = -EOPNOTSUPP;
		break;

	case SIOCSIWRETRY:

		rc = iwctl_siwretry(dev, NULL, &(wrq->u.retry), NULL);
		break;

	case SIOCGIWRETRY:

		rc = iwctl_giwretry(dev, NULL, &(wrq->u.retry), NULL);
		break;

		// Get range of parameters
	case SIOCGIWRANGE:

		{
			struct iw_range range;

			rc = iwctl_giwrange(dev, NULL, &(wrq->u.data), (char *) &range);
			if (copy_to_user(wrq->u.data.pointer, &range, sizeof(struct iw_range)))
				rc = -EFAULT;
		}

		break;

	case SIOCGIWPOWER:

		rc = iwctl_giwpower(dev, NULL, &(wrq->u.power), NULL);
		break;


	case SIOCSIWPOWER:

		rc = iwctl_siwpower(dev, NULL, &(wrq->u.power), NULL);
		break;


	case SIOCGIWSENS:

	    rc = iwctl_giwsens(dev, NULL, &(wrq->u.sens), NULL);
		break;

	case SIOCSIWSENS:
        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCSIWSENS \n");
		rc = -EOPNOTSUPP;
		break;

	case SIOCGIWAPLIST:
	    {
            char buffer[IW_MAX_AP * (sizeof(struct sockaddr) + sizeof(struct iw_quality))];

		    if (wrq->u.data.pointer) {
		        rc = iwctl_giwaplist(dev, NULL, &(wrq->u.data), buffer);
		        if (rc == 0) {
                    if (copy_to_user(wrq->u.data.pointer,
					                buffer,
					               (wrq->u.data.length * (sizeof(struct sockaddr) +  sizeof(struct iw_quality)))
				        ))
				    rc = -EFAULT;
		        }
            }
        }
		break;


#ifdef WIRELESS_SPY
		// Set the spy list
	case SIOCSIWSPY:

        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCSIWSPY \n");
		rc = -EOPNOTSUPP;
		break;

		// Get the spy list
	case SIOCGIWSPY:

        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCSIWSPY \n");
		rc = -EOPNOTSUPP;
		break;

#endif // WIRELESS_SPY

	case SIOCGIWPRIV:
        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCGIWPRIV \n");
		rc = -EOPNOTSUPP;
/*
		if(wrq->u.data.pointer) {
			wrq->u.data.length = sizeof(iwctl_private_args) / sizeof( iwctl_private_args[0]);

			if(copy_to_user(wrq->u.data.pointer,
					(u_char *) iwctl_private_args,
					sizeof(iwctl_private_args)))
				rc = -EFAULT;
		}
*/
		break;


//2008-0409-07, <Add> by Einsn Liu
#ifdef  WPA_SUPPLICANT_DRIVER_WEXT_SUPPORT
	case SIOCSIWAUTH:
		DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCSIWAUTH \n");
		rc = iwctl_siwauth(dev, NULL, &(wrq->u.param), NULL);
		break;

	case SIOCGIWAUTH:
		DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCGIWAUTH \n");
		rc = iwctl_giwauth(dev, NULL, &(wrq->u.param), NULL);
		break;

	case SIOCSIWGENIE:
		DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCSIWGENIE \n");
		rc = iwctl_siwgenie(dev, NULL, &(wrq->u.data), wrq->u.data.pointer);
		break;

	case SIOCGIWGENIE:
		DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCGIWGENIE \n");
		rc = iwctl_giwgenie(dev, NULL, &(wrq->u.data), wrq->u.data.pointer);
		break;

	case SIOCSIWENCODEEXT:
		{
			char extra[sizeof(struct iw_encode_ext)+MAX_KEY_LEN+1];
			DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCSIWENCODEEXT \n");
			if(wrq->u.encoding.pointer){
				memset(extra, 0, sizeof(struct iw_encode_ext)+MAX_KEY_LEN+1);
				if(wrq->u.encoding.length > (sizeof(struct iw_encode_ext)+ MAX_KEY_LEN)){
					rc = -E2BIG;
					break;
				}
				if(copy_from_user(extra, wrq->u.encoding.pointer,wrq->u.encoding.length)){
					rc = -EFAULT;
					break;
				}
			}else if(wrq->u.encoding.length != 0){
				rc = -EINVAL;
				break;
			}
			rc = iwctl_siwencodeext(dev, NULL, &(wrq->u.encoding), extra);
		}
		break;

	case SIOCGIWENCODEEXT:
		DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCGIWENCODEEXT \n");
		rc = iwctl_giwencodeext(dev, NULL, &(wrq->u.encoding), NULL);
		break;

	case SIOCSIWMLME:
		DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO " SIOCSIWMLME \n");
		rc = iwctl_siwmlme(dev, NULL, &(wrq->u.data), wrq->u.data.pointer);
		break;

#endif // #ifdef WPA_SUPPLICANT_DRIVER_WEXT_SUPPORT
//End Add -- //2008-0409-07, <Add> by Einsn Liu

    case IOCTL_CMD_TEST:

		if (!(pDevice->flags & DEVICE_FLAGS_OPENED)) {
		    rc = -EFAULT;
		    break;
		} else {
		    rc = 0;
		}
        pReq = (PSCmdRequest)rq;
        pReq->wResult = MAGIC_CODE;
        break;

    case IOCTL_CMD_SET:

               #ifdef SndEvt_ToAPI
                  if((((PSCmdRequest)rq)->wCmdCode !=WLAN_CMD_SET_EVT) &&
		       !(pDevice->flags & DEVICE_FLAGS_OPENED))
	      #else
		if (!(pDevice->flags & DEVICE_FLAGS_OPENED) &&
		       (((PSCmdRequest)rq)->wCmdCode !=WLAN_CMD_SET_WPA))
	      #endif
		{
		    rc = -EFAULT;
		    break;
		} else {
		    rc = 0;
		}

	    if (test_and_set_bit( 0, (void*)&(pMgmt->uCmdBusy))) {
		    return -EBUSY;
	    }
        rc = private_ioctl(pDevice, rq);
        clear_bit( 0, (void*)&(pMgmt->uCmdBusy));
        break;

    case IOCTL_CMD_HOSTAPD:


	rc = hostap_ioctl(pDevice, &wrq->u.data);
        break;

    case IOCTL_CMD_WPA:

	rc = wpa_ioctl(pDevice, &wrq->u.data);
        break;

	case SIOCETHTOOL:
        return ethtool_ioctl(dev, (void *) rq->ifr_data);
	// All other calls are currently unsupported

	default:
		rc = -EOPNOTSUPP;
        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO "Ioctl command not support..%x\n", cmd);


    }
