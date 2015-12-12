switch (cmd) {
	case PPPIOCSMRU:
		if (get_user(val, p))
			break;
		ppp->mru = val;
		err = 0;
		break;

	case PPPIOCSFLAGS:
		if (get_user(val, p))
			break;
		ppp_lock(ppp);
		cflags = ppp->flags & ~val;
#ifdef CONFIG_PPP_MULTILINK
		if (!(ppp->flags & SC_MULTILINK) && (val & SC_MULTILINK))
			ppp->nextseq = 0;
#endif
		ppp->flags = val & SC_FLAG_BITS;
		ppp_unlock(ppp);
		if (cflags & SC_CCP_OPEN)
			ppp_ccp_closed(ppp);
		err = 0;
		break;

	case PPPIOCGFLAGS:
		val = ppp->flags | ppp->xstate | ppp->rstate;
		if (put_user(val, p))
			break;
		err = 0;
		break;

	case PPPIOCSCOMPRESS:
		err = ppp_set_compress(ppp, arg);
		break;

	case PPPIOCGUNIT:
		if (put_user(ppp->file.index, p))
			break;
		err = 0;
		break;

	case PPPIOCSDEBUG:
		if (get_user(val, p))
			break;
		ppp->debug = val;
		err = 0;
		break;

	case PPPIOCGDEBUG:
		if (put_user(ppp->debug, p))
			break;
		err = 0;
		break;

	case PPPIOCGIDLE:
		idle.xmit_idle = (jiffies - ppp->last_xmit) / HZ;
		idle.recv_idle = (jiffies - ppp->last_recv) / HZ;
		if (copy_to_user(argp, &idle, sizeof(idle)))
			break;
		err = 0;
		break;

	case PPPIOCSMAXCID:
		if (get_user(val, p))
			break;
		val2 = 15;
		if ((val >> 16) != 0) {
			val2 = val >> 16;
			val &= 0xffff;
		}
		vj = slhc_init(val2+1, val+1);
		if (IS_ERR(vj)) {
			err = PTR_ERR(vj);
			break;
		}
		ppp_lock(ppp);
		if (ppp->vj)
			slhc_free(ppp->vj);
		ppp->vj = vj;
		ppp_unlock(ppp);
		err = 0;
		break;

	case PPPIOCGNPMODE:
	case PPPIOCSNPMODE:
		if (copy_from_user(&npi, argp, sizeof(npi)))
			break;
		err = proto_to_npindex(npi.protocol);
		if (err < 0)
			break;
		i = err;
		if (cmd == PPPIOCGNPMODE) {
			err = -EFAULT;
			npi.mode = ppp->npmode[i];
			if (copy_to_user(argp, &npi, sizeof(npi)))
				break;
		} else {
			ppp->npmode[i] = npi.mode;
			/* we may be able to transmit more packets now (??) */
			netif_wake_queue(ppp->dev);
		}
		err = 0;
		break;

#ifdef CONFIG_PPP_FILTER
	case PPPIOCSPASS:
	{
		struct sock_filter *code;

		err = get_filter(argp, &code);
		if (err >= 0) {
			struct bpf_prog *pass_filter = NULL;
			struct sock_fprog_kern fprog = {
				.len = err,
				.filter = code,
			};

			err = 0;
			if (fprog.filter)
				err = bpf_prog_create(&pass_filter, &fprog);
			if (!err) {
				ppp_lock(ppp);
				if (ppp->pass_filter)
					bpf_prog_destroy(ppp->pass_filter);
				ppp->pass_filter = pass_filter;
				ppp_unlock(ppp);
			}
			kfree(code);
		}
		break;
	}
	case PPPIOCSACTIVE:
	{
		struct sock_filter *code;

		err = get_filter(argp, &code);
		if (err >= 0) {
			struct bpf_prog *active_filter = NULL;
			struct sock_fprog_kern fprog = {
				.len = err,
				.filter = code,
			};

			err = 0;
			if (fprog.filter)
				err = bpf_prog_create(&active_filter, &fprog);
			if (!err) {
				ppp_lock(ppp);
				if (ppp->active_filter)
					bpf_prog_destroy(ppp->active_filter);
				ppp->active_filter = active_filter;
				ppp_unlock(ppp);
			}
			kfree(code);
		}
		break;
	}
#endif /* CONFIG_PPP_FILTER */

#ifdef CONFIG_PPP_MULTILINK
	case PPPIOCSMRRU:
		if (get_user(val, p))
			break;
		ppp_recv_lock(ppp);
		ppp->mrru = val;
		ppp_recv_unlock(ppp);
		err = 0;
		break;
#endif /* CONFIG_PPP_MULTILINK */

	default:
		err = -ENOTTY;
	}
