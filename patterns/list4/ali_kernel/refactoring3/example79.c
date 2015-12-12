switch (c->command) {
		case ISDN_STAT_BSENT:
			if (i < 0)
				return -1;
			if (dev->global_flags & ISDN_GLOBAL_STOPPED)
				return 0;
			if (isdn_net_stat_callback(i, c))
				return 0;
			if (isdn_v110_stat_callback(i, c))
				return 0;
			if (isdn_tty_stat_callback(i, c))
				return 0;
			wake_up_interruptible(&dev->drv[di]->snd_waitq[c->arg]);
			break;
		case ISDN_STAT_STAVAIL:
			dev->drv[di]->stavail += c->arg;
			wake_up_interruptible(&dev->drv[di]->st_waitq);
			break;
		case ISDN_STAT_RUN:
			dev->drv[di]->flags |= DRV_FLAG_RUNNING;
			for (i = 0; i < ISDN_MAX_CHANNELS; i++)
				if (dev->drvmap[i] == di)
					isdn_all_eaz(di, dev->chanmap[i]);
			set_global_features();
			break;
		case ISDN_STAT_STOP:
			dev->drv[di]->flags &= ~DRV_FLAG_RUNNING;
			break;
		case ISDN_STAT_ICALL:
			if (i < 0)
				return -1;
#ifdef ISDN_DEBUG_STATCALLB
			printk(KERN_DEBUG "ICALL (net): %d %ld %s\n", di, c->arg, c->parm.num);
#endif
			if (dev->global_flags & ISDN_GLOBAL_STOPPED) {
				cmd.driver = di;
				cmd.arg = c->arg;
				cmd.command = ISDN_CMD_HANGUP;
				isdn_command(&cmd);
				return 0;
			}
			/* Try to find a network-interface which will accept incoming call */
			r = ((c->command == ISDN_STAT_ICALLW) ? 0 : isdn_net_find_icall(di, c->arg, i, &c->parm.setup));
			switch (r) {
				case 0:
					/* No network-device replies.
					 * Try ttyI's.
					 * These return 0 on no match, 1 on match and
					 * 3 on eventually match, if CID is longer.
					 */
                                        if (c->command == ISDN_STAT_ICALL)
					  if ((retval = isdn_tty_find_icall(di, c->arg, &c->parm.setup))) return(retval);
#ifdef CONFIG_ISDN_DIVERSION 
                                         if (divert_if)
                 	                  if ((retval = divert_if->stat_callback(c))) 
					    return(retval); /* processed */
#endif /* CONFIG_ISDN_DIVERSION */                       
					if ((!retval) && (dev->drv[di]->flags & DRV_FLAG_REJBUS)) {
						/* No tty responding */
						cmd.driver = di;
						cmd.arg = c->arg;
						cmd.command = ISDN_CMD_HANGUP;
						isdn_command(&cmd);
						retval = 2;
					}
					break;
				case 1:
					/* Schedule connection-setup */
					isdn_net_dial();
					cmd.driver = di;
					cmd.arg = c->arg;
					cmd.command = ISDN_CMD_ACCEPTD;
					for ( p = dev->netdev; p; p = p->next )
						if ( p->local->isdn_channel == cmd.arg )
						{
							strcpy( cmd.parm.setup.eazmsn, p->local->msn );
							isdn_command(&cmd);
							retval = 1;
							break;
						}
					break;

				case 2:	/* For calling back, first reject incoming call ... */
				case 3:	/* Interface found, but down, reject call actively  */
					retval = 2;
					printk(KERN_INFO "isdn: Rejecting Call\n");
					cmd.driver = di;
					cmd.arg = c->arg;
					cmd.command = ISDN_CMD_HANGUP;
					isdn_command(&cmd);
					if (r == 3)
						break;
					/* Fall through */
				case 4:
					/* ... then start callback. */
					isdn_net_dial();
					break;
				case 5:
					/* Number would eventually match, if longer */
					retval = 3;
					break;
			}
#ifdef ISDN_DEBUG_STATCALLB
			printk(KERN_DEBUG "ICALL: ret=%d\n", retval);
#endif
			return retval;
			break;
		case ISDN_STAT_CINF:
			if (i < 0)
				return -1;
#ifdef ISDN_DEBUG_STATCALLB
			printk(KERN_DEBUG "CINF: %ld %s\n", c->arg, c->parm.num);
#endif
			if (dev->global_flags & ISDN_GLOBAL_STOPPED)
				return 0;
			if (strcmp(c->parm.num, "0"))
				isdn_net_stat_callback(i, c);
			isdn_tty_stat_callback(i, c);
			break;
		case ISDN_STAT_CAUSE:
#ifdef ISDN_DEBUG_STATCALLB
			printk(KERN_DEBUG "CAUSE: %ld %s\n", c->arg, c->parm.num);
#endif
			printk(KERN_INFO "isdn: %s,ch%ld cause: %s\n",
			       dev->drvid[di], c->arg, c->parm.num);
			isdn_tty_stat_callback(i, c);
#ifdef CONFIG_ISDN_DIVERSION
                        if (divert_if)
                         divert_if->stat_callback(c); 
#endif /* CONFIG_ISDN_DIVERSION */
			break;
		case ISDN_STAT_DISPLAY:
#ifdef ISDN_DEBUG_STATCALLB
			printk(KERN_DEBUG "DISPLAY: %ld %s\n", c->arg, c->parm.display);
#endif
			isdn_tty_stat_callback(i, c);
#ifdef CONFIG_ISDN_DIVERSION
                        if (divert_if)
                         divert_if->stat_callback(c); 
#endif /* CONFIG_ISDN_DIVERSION */
			break;
		case ISDN_STAT_DCONN:
			if (i < 0)
				return -1;
#ifdef ISDN_DEBUG_STATCALLB
			printk(KERN_DEBUG "DCONN: %ld\n", c->arg);
#endif
			if (dev->global_flags & ISDN_GLOBAL_STOPPED)
				return 0;
			/* Find any net-device, waiting for D-channel setup */
			if (isdn_net_stat_callback(i, c))
				break;
			isdn_v110_stat_callback(i, c);
			/* Find any ttyI, waiting for D-channel setup */
			if (isdn_tty_stat_callback(i, c)) {
				cmd.driver = di;
				cmd.arg = c->arg;
				cmd.command = ISDN_CMD_ACCEPTB;
				isdn_command(&cmd);
				break;
			}
			break;
		case ISDN_STAT_DHUP:
			if (i < 0)
				return -1;
#ifdef ISDN_DEBUG_STATCALLB
			printk(KERN_DEBUG "DHUP: %ld\n", c->arg);
#endif
			if (dev->global_flags & ISDN_GLOBAL_STOPPED)
				return 0;
			dev->drv[di]->online &= ~(1 << (c->arg));
			isdn_info_update();
			/* Signal hangup to network-devices */
			if (isdn_net_stat_callback(i, c))
				break;
			isdn_v110_stat_callback(i, c);
			if (isdn_tty_stat_callback(i, c))
				break;
#ifdef CONFIG_ISDN_DIVERSION
                        if (divert_if)
                         divert_if->stat_callback(c); 
#endif /* CONFIG_ISDN_DIVERSION */
			break;
			break;
		case ISDN_STAT_BCONN:
			if (i < 0)
				return -1;
#ifdef ISDN_DEBUG_STATCALLB
			printk(KERN_DEBUG "BCONN: %ld\n", c->arg);
#endif
			/* Signal B-channel-connect to network-devices */
			if (dev->global_flags & ISDN_GLOBAL_STOPPED)
				return 0;
			dev->drv[di]->online |= (1 << (c->arg));
			isdn_info_update();
			if (isdn_net_stat_callback(i, c))
				break;
			isdn_v110_stat_callback(i, c);
			if (isdn_tty_stat_callback(i, c))
				break;
			break;
		case ISDN_STAT_BHUP:
			if (i < 0)
				return -1;
#ifdef ISDN_DEBUG_STATCALLB
			printk(KERN_DEBUG "BHUP: %ld\n", c->arg);
#endif
			if (dev->global_flags & ISDN_GLOBAL_STOPPED)
				return 0;
			dev->drv[di]->online &= ~(1 << (c->arg));
			isdn_info_update();
#ifdef CONFIG_ISDN_X25
			/* Signal hangup to network-devices */
			if (isdn_net_stat_callback(i, c))
				break;
#endif
			isdn_v110_stat_callback(i, c);
			if (isdn_tty_stat_callback(i, c))
				break;
			break;
		case ISDN_STAT_NODCH:
			if (i < 0)
				return -1;
#ifdef ISDN_DEBUG_STATCALLB
			printk(KERN_DEBUG "NODCH: %ld\n", c->arg);
#endif
			if (dev->global_flags & ISDN_GLOBAL_STOPPED)
				return 0;
			if (isdn_net_stat_callback(i, c))
				break;
			if (isdn_tty_stat_callback(i, c))
				break;
			break;
		case ISDN_STAT_ADDCH:
			spin_lock_irqsave(&dev->lock, flags);
			if (isdn_add_channels(dev->drv[di], di, c->arg, 1)) {
				spin_unlock_irqrestore(&dev->lock, flags);
				return -1;
			}
			spin_unlock_irqrestore(&dev->lock, flags);
			isdn_info_update();
			break;
		case ISDN_STAT_DISCH:
			spin_lock_irqsave(&dev->lock, flags);
			for (i = 0; i < ISDN_MAX_CHANNELS; i++)
				if ((dev->drvmap[i] == di) &&
				    (dev->chanmap[i] == c->arg)) {
				    if (c->parm.num[0])
				      dev->usage[i] &= ~ISDN_USAGE_DISABLED;
				    else
				      if (USG_NONE(dev->usage[i])) {
					dev->usage[i] |= ISDN_USAGE_DISABLED;
				      }
				      else 
					retval = -1;
				    break;
				}
			spin_unlock_irqrestore(&dev->lock, flags);
			isdn_info_update();
			break;
		case ISDN_STAT_UNLOAD:
			while (dev->drv[di]->locks > 0) {
				isdn_unlock_driver(dev->drv[di]);
			}
			spin_lock_irqsave(&dev->lock, flags);
			isdn_tty_stat_callback(i, c);
			for (i = 0; i < ISDN_MAX_CHANNELS; i++)
				if (dev->drvmap[i] == di) {
					dev->drvmap[i] = -1;
					dev->chanmap[i] = -1;
					dev->usage[i] &= ~ISDN_USAGE_DISABLED;
				}
			dev->drivers--;
			dev->channels -= dev->drv[di]->channels;
			kfree(dev->drv[di]->rcverr);
			kfree(dev->drv[di]->rcvcount);
			for (i = 0; i < dev->drv[di]->channels; i++)
				skb_queue_purge(&dev->drv[di]->rpqueue[i]);
			kfree(dev->drv[di]->rpqueue);
			kfree(dev->drv[di]->rcv_waitq);
			kfree(dev->drv[di]);
			dev->drv[di] = NULL;
			dev->drvid[di][0] = '\0';
			isdn_info_update();
			set_global_features();
			spin_unlock_irqrestore(&dev->lock, flags);
			return 0;
		case ISDN_STAT_L1ERR:
			break;
		case CAPI_PUT_MESSAGE:
			return(isdn_capi_rec_hl_msg(&c->parm.cmsg));
#ifdef CONFIG_ISDN_TTY_FAX
		case ISDN_STAT_FAXIND:
			isdn_tty_stat_callback(i, c);
			break;
#endif
#ifdef CONFIG_ISDN_AUDIO
		case ISDN_STAT_AUDIO:
			isdn_tty_stat_callback(i, c);
			break;
#endif
#ifdef CONFIG_ISDN_DIVERSION
	        case ISDN_STAT_PROT:
	        case ISDN_STAT_REDIR:
                        if (divert_if)
                          return(divert_if->stat_callback(c));
#endif /* CONFIG_ISDN_DIVERSION */
		default:
			return -1;
	}
