switch (cmd) {
	case PPPIOCBUNDLE:
#ifdef CONFIG_ISDN_MPP
		if (!(is->state & IPPP_CONNECT))
			return -EINVAL;
		if ((r = get_arg(argp, &val, sizeof(val))))
			return r;
		printk(KERN_DEBUG "iPPP-bundle: minor: %d, slave unit: %d, master unit: %d\n",
		       (int) min, (int) is->unit, (int) val);
		return isdn_ppp_bundle(is, val);
#else
		return -1;
#endif
		break;
	case PPPIOCGUNIT:	/* get ppp/isdn unit number */
		if ((r = set_arg(argp, &is->unit, sizeof(is->unit))))
			return r;
		break;
	case PPPIOCGIFNAME:
		if (!lp)
			return -EINVAL;
		if ((r = set_arg(argp, lp->netdev->dev->name,
				 strlen(lp->netdev->dev->name))))
			return r;
		break;
	case PPPIOCGMPFLAGS:	/* get configuration flags */
		if ((r = set_arg(argp, &is->mpppcfg, sizeof(is->mpppcfg))))
			return r;
		break;
	case PPPIOCSMPFLAGS:	/* set configuration flags */
		if ((r = get_arg(argp, &val, sizeof(val))))
			return r;
		is->mpppcfg = val;
		break;
	case PPPIOCGFLAGS:	/* get configuration flags */
		if ((r = set_arg(argp, &is->pppcfg, sizeof(is->pppcfg))))
			return r;
		break;
	case PPPIOCSFLAGS:	/* set configuration flags */
		if ((r = get_arg(argp, &val, sizeof(val)))) {
			return r;
		}
		if (val & SC_ENABLE_IP && !(is->pppcfg & SC_ENABLE_IP) && (is->state & IPPP_CONNECT)) {
			if (lp) {
				/* OK .. we are ready to send buffers */
				is->pppcfg = val; /* isdn_ppp_xmit test for SC_ENABLE_IP !!! */
				netif_wake_queue(lp->netdev->dev);
				break;
			}
		}
		is->pppcfg = val;
		break;
	case PPPIOCGIDLE:	/* get idle time information */
		if (lp) {
			struct ppp_idle pidle;
			pidle.xmit_idle = pidle.recv_idle = lp->huptimer;
			if ((r = set_arg(argp, &pidle, sizeof(struct ppp_idle))))
				return r;
		}
		break;
	case PPPIOCSMRU:	/* set receive unit size for PPP */
		if ((r = get_arg(argp, &val, sizeof(val))))
			return r;
		is->mru = val;
		break;
	case PPPIOCSMPMRU:
		break;
	case PPPIOCSMPMTU:
		break;
	case PPPIOCSMAXCID:	/* set the maximum compression slot id */
		if ((r = get_arg(argp, &val, sizeof(val))))
			return r;
		val++;
		if (is->maxcid != val) {
#ifdef CONFIG_ISDN_PPP_VJ
			struct slcompress *sltmp;
#endif
			if (is->debug & 0x1)
				printk(KERN_DEBUG "ippp, ioctl: changed MAXCID to %ld\n", val);
			is->maxcid = val;
#ifdef CONFIG_ISDN_PPP_VJ
			sltmp = slhc_init(16, val);
			if (!sltmp) {
				printk(KERN_ERR "ippp, can't realloc slhc struct\n");
				return -ENOMEM;
			}
			if (is->slcomp)
				slhc_free(is->slcomp);
			is->slcomp = sltmp;
#endif
		}
		break;
	case PPPIOCGDEBUG:
		if ((r = set_arg(argp, &is->debug, sizeof(is->debug))))
			return r;
		break;
	case PPPIOCSDEBUG:
		if ((r = get_arg(argp, &val, sizeof(val))))
			return r;
		is->debug = val;
		break;
	case PPPIOCGCOMPRESSORS:
	{
		unsigned long protos[8] = {0,};
		struct isdn_ppp_compressor *ipc = ipc_head;
		while (ipc) {
			j = ipc->num / (sizeof(long) * 8);
			i = ipc->num % (sizeof(long) * 8);
			if (j < 8)
				protos[j] |= (1UL << i);
			ipc = ipc->next;
		}
		if ((r = set_arg(argp, protos, 8 * sizeof(long))))
			return r;
	}
	break;
	case PPPIOCSCOMPRESSOR:
		if ((r = get_arg(argp, &data, sizeof(struct isdn_ppp_comp_data))))
			return r;
		return isdn_ppp_set_compressor(is, &data);
	case PPPIOCGCALLINFO:
	{
		struct pppcallinfo pci;
		memset((char *)&pci, 0, sizeof(struct pppcallinfo));
		if (lp)
		{
			strncpy(pci.local_num, lp->msn, 63);
			if (lp->dial) {
				strncpy(pci.remote_num, lp->dial->num, 63);
			}
			pci.charge_units = lp->charge;
			if (lp->outgoing)
				pci.calltype = CALLTYPE_OUTGOING;
			else
				pci.calltype = CALLTYPE_INCOMING;
			if (lp->flags & ISDN_NET_CALLBACK)
				pci.calltype |= CALLTYPE_CALLBACK;
		}
		return set_arg(argp, &pci, sizeof(struct pppcallinfo));
	}
#ifdef CONFIG_IPPP_FILTER
	case PPPIOCSPASS:
	{
		struct sock_filter *code;
		int len = get_filter(argp, &code);
		if (len < 0)
			return len;
		kfree(is->pass_filter);
		is->pass_filter = code;
		is->pass_len = len;
		break;
	}
	case PPPIOCSACTIVE:
	{
		struct sock_filter *code;
		int len = get_filter(argp, &code);
		if (len < 0)
			return len;
		kfree(is->active_filter);
		is->active_filter = code;
		is->active_len = len;
		break;
	}
#endif /* CONFIG_IPPP_FILTER */
	default:
		break;
	}
