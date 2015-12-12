switch(cmd)
	{
#ifdef RALINK_ATE
#ifdef RALINK_28xx_QA
		case RTPRIV_IOCTL_ATE:
			{
				RtmpDoAte(pAd, wrq);
			}
			break;
#endif // RALINK_28xx_QA //
#endif // RALINK_ATE //
        case SIOCGIFHWADDR:
			DBGPRINT(RT_DEBUG_TRACE, ("IOCTL::SIOCGIFHWADDR\n"));
			memcpy(wrq->u.name, pAd->CurrentAddress, ETH_ALEN);
			break;
		case SIOCGIWNAME:
        {
		char *name=&wrq->u.name[0];
		rt_ioctl_giwname(net_dev, NULL, name, NULL);
            break;
		}
		case SIOCGIWESSID:  //Get ESSID
        {
		struct iw_point *essid=&wrq->u.essid;
		rt_ioctl_giwessid(net_dev, NULL, essid, essid->pointer);
            break;
		}
		case SIOCSIWESSID:  //Set ESSID
		{
		struct iw_point	*essid=&wrq->u.essid;
		rt_ioctl_siwessid(net_dev, NULL, essid, essid->pointer);
            break;
		}
		case SIOCSIWNWID:   // set network id (the cell)
		case SIOCGIWNWID:   // get network id
			Status = -EOPNOTSUPP;
			break;
		case SIOCSIWFREQ:   //set channel/frequency (Hz)
		{
		struct iw_freq *freq=&wrq->u.freq;
		rt_ioctl_siwfreq(net_dev, NULL, freq, NULL);
			break;
		}
		case SIOCGIWFREQ:   // get channel/frequency (Hz)
		{
		struct iw_freq *freq=&wrq->u.freq;
		rt_ioctl_giwfreq(net_dev, NULL, freq, NULL);
			break;
		}
		case SIOCSIWNICKN: //set node name/nickname
		{
		//struct iw_point *data=&wrq->u.data;
		//rt_ioctl_siwnickn(net_dev, NULL, data, NULL);
			break;
			}
		case SIOCGIWNICKN: //get node name/nickname
        {
			struct iw_point	*erq = NULL;
		erq = &wrq->u.data;
            erq->length = strlen((PSTRING) pAd->nickname);
            Status = copy_to_user(erq->pointer, pAd->nickname, erq->length);
			break;
		}
		case SIOCGIWRATE:   //get default bit rate (bps)
		    rt_ioctl_giwrate(net_dev, NULL, &wrq->u, NULL);
            break;
	    case SIOCSIWRATE:  //set default bit rate (bps)
	        rt_ioctl_siwrate(net_dev, NULL, &wrq->u, NULL);
            break;
        case SIOCGIWRTS:  // get RTS/CTS threshold (bytes)
		{
		struct iw_param *rts=&wrq->u.rts;
		rt_ioctl_giwrts(net_dev, NULL, rts, NULL);
            break;
		}
        case SIOCSIWRTS:  //set RTS/CTS threshold (bytes)
		{
		struct iw_param *rts=&wrq->u.rts;
		rt_ioctl_siwrts(net_dev, NULL, rts, NULL);
            break;
		}
        case SIOCGIWFRAG:  //get fragmentation thr (bytes)
		{
		struct iw_param *frag=&wrq->u.frag;
		rt_ioctl_giwfrag(net_dev, NULL, frag, NULL);
            break;
		}
        case SIOCSIWFRAG:  //set fragmentation thr (bytes)
		{
		struct iw_param *frag=&wrq->u.frag;
		rt_ioctl_siwfrag(net_dev, NULL, frag, NULL);
            break;
		}
        case SIOCGIWENCODE:  //get encoding token & mode
		{
		struct iw_point *erq=&wrq->u.encoding;
		if(erq)
			rt_ioctl_giwencode(net_dev, NULL, erq, erq->pointer);
            break;
		}
        case SIOCSIWENCODE:  //set encoding token & mode
		{
		struct iw_point *erq=&wrq->u.encoding;
		if(erq)
			rt_ioctl_siwencode(net_dev, NULL, erq, erq->pointer);
            break;
		}
		case SIOCGIWAP:     //get access point MAC addresses
		{
		struct sockaddr *ap_addr=&wrq->u.ap_addr;
		rt_ioctl_giwap(net_dev, NULL, ap_addr, ap_addr->sa_data);
			break;
		}
	    case SIOCSIWAP:  //set access point MAC addresses
		{
		struct sockaddr *ap_addr=&wrq->u.ap_addr;
		rt_ioctl_siwap(net_dev, NULL, ap_addr, ap_addr->sa_data);
            break;
		}
		case SIOCGIWMODE:   //get operation mode
		{
		__u32 *mode=&wrq->u.mode;
		rt_ioctl_giwmode(net_dev, NULL, mode, NULL);
            break;
		}
		case SIOCSIWMODE:   //set operation mode
		{
		__u32 *mode=&wrq->u.mode;
		rt_ioctl_siwmode(net_dev, NULL, mode, NULL);
            break;
		}
		case SIOCGIWSENS:   //get sensitivity (dBm)
		case SIOCSIWSENS:	//set sensitivity (dBm)
		case SIOCGIWPOWER:  //get Power Management settings
		case SIOCSIWPOWER:  //set Power Management settings
		case SIOCGIWTXPOW:  //get transmit power (dBm)
		case SIOCSIWTXPOW:  //set transmit power (dBm)
		case SIOCGIWRANGE:	//Get range of parameters
		case SIOCGIWRETRY:	//get retry limits and lifetime
		case SIOCSIWRETRY:	//set retry limits and lifetime
			Status = -EOPNOTSUPP;
			break;
		case RT_PRIV_IOCTL:
        case RT_PRIV_IOCTL_EXT:
			subcmd = wrq->u.data.flags;
			if( subcmd & OID_GET_SET_TOGGLE)
				Status = RTMPSetInformation(pAd, rq, subcmd);
			else
				Status = RTMPQueryInformation(pAd, rq, subcmd);
			break;
		case SIOCGIWPRIV:
			if (wrq->u.data.pointer)
			{
				if ( access_ok(VERIFY_WRITE, wrq->u.data.pointer, sizeof(privtab)) != TRUE)
					break;
				wrq->u.data.length = sizeof(privtab) / sizeof(privtab[0]);
				if (copy_to_user(wrq->u.data.pointer, privtab, sizeof(privtab)))
					Status = -EFAULT;
			}
			break;
		case RTPRIV_IOCTL_SET:
			if(access_ok(VERIFY_READ, wrq->u.data.pointer, wrq->u.data.length) != TRUE)
					break;
			rt_ioctl_setparam(net_dev, NULL, NULL, wrq->u.data.pointer);
			break;
		case RTPRIV_IOCTL_GSITESURVEY:
			RTMPIoctlGetSiteSurvey(pAd, wrq);
		    break;
#ifdef DBG
		case RTPRIV_IOCTL_MAC:
			RTMPIoctlMAC(pAd, wrq);
			break;
		case RTPRIV_IOCTL_E2P:
			RTMPIoctlE2PROM(pAd, wrq);
			break;
#ifdef RTMP_RF_RW_SUPPORT
		case RTPRIV_IOCTL_RF:
			RTMPIoctlRF(pAd, wrq);
			break;
#endif // RTMP_RF_RW_SUPPORT //
#endif // DBG //

        case SIOCETHTOOL:
                break;
		default:
			DBGPRINT(RT_DEBUG_ERROR, ("IOCTL::unknown IOCTL's cmd = 0x%08x\n", cmd));
			Status = -EOPNOTSUPP;
			break;
	}
