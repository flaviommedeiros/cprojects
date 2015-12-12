switch (cmd) {
		case ISDN_STAT_BSENT:
			/* A packet has successfully been sent out */
			if ((lp->flags & ISDN_NET_CONNECTED) &&
			    (!lp->dialstate)) {
				isdn_net_dec_frame_cnt(lp);
				lp->stats.tx_packets++;
				lp->stats.tx_bytes += c->parm.length;
			}
			return 1;
		case ISDN_STAT_DCONN:
			/* D-Channel is up */
			switch (lp->dialstate) {
			case 4:
			case 7:
			case 8:
				lp->dialstate++;
				return 1;
			case 12:
				lp->dialstate = 5;
				return 1;
			}
			break;
		case ISDN_STAT_DHUP:
			/* Either D-Channel-hangup or error during dialout */
#ifdef CONFIG_ISDN_X25
			/* If we are not connencted then dialing had
			   failed. If there are generic encap protocol
			   receiver routines signal the closure of
			   the link*/

			if (!(lp->flags & ISDN_NET_CONNECTED)
			    && pops && pops->disconn_ind)
				pops->disconn_ind(cprot);
#endif /* CONFIG_ISDN_X25 */
			if ((!lp->dialstate) && (lp->flags & ISDN_NET_CONNECTED)) {
				if (lp->p_encap == ISDN_NET_ENCAP_CISCOHDLCK)
					isdn_net_ciscohdlck_disconnected(lp);
#ifdef CONFIG_ISDN_PPP
				if (lp->p_encap == ISDN_NET_ENCAP_SYNCPPP)
					isdn_ppp_free(lp);
#endif
				isdn_net_lp_disconnected(lp);
				isdn_all_eaz(lp->isdn_device, lp->isdn_channel);
				printk(KERN_INFO "%s: remote hangup\n", p->dev->name);
				printk(KERN_INFO "%s: Chargesum is %d\n", p->dev->name,
				       lp->charge);
				isdn_net_unbind_channel(lp);
				return 1;
			}
			break;
#ifdef CONFIG_ISDN_X25
		case ISDN_STAT_BHUP:
			/* B-Channel-hangup */
			/* try if there are generic encap protocol
			   receiver routines and signal the closure of
			   the link */
			if (pops && pops->disconn_ind) {
				pops->disconn_ind(cprot);
				return 1;
			}
			break;
#endif /* CONFIG_ISDN_X25 */
		case ISDN_STAT_BCONN:
			/* B-Channel is up */
			isdn_net_zero_frame_cnt(lp);
			switch (lp->dialstate) {
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 12:
				if (lp->dialstate <= 6) {
					dev->usage[idx] |= ISDN_USAGE_OUTGOING;
					isdn_info_update();
				} else
					dev->rx_netdev[idx] = p;
				lp->dialstate = 0;
				isdn_timer_ctrl(ISDN_TIMER_NETHANGUP, 1);
				if (lp->p_encap == ISDN_NET_ENCAP_CISCOHDLCK)
					isdn_net_ciscohdlck_connected(lp);
				if (lp->p_encap != ISDN_NET_ENCAP_SYNCPPP) {
					if (lp->master) { /* is lp a slave? */
						isdn_net_dev *nd = ISDN_MASTER_PRIV(lp)->netdev;
						isdn_net_add_to_bundle(nd, lp);
					}
				}
				printk(KERN_INFO "isdn_net: %s connected\n", p->dev->name);
				/* If first Chargeinfo comes before B-Channel connect,
				 * we correct the timestamp here.
				 */
				lp->chargetime = jiffies;

				/* reset dial-timeout */
				lp->dialstarted = 0;
				lp->dialwait_timer = 0;

#ifdef CONFIG_ISDN_PPP
				if (lp->p_encap == ISDN_NET_ENCAP_SYNCPPP)
					isdn_ppp_wakeup_daemon(lp);
#endif
#ifdef CONFIG_ISDN_X25
				/* try if there are generic concap receiver routines */
				if (pops)
					if (pops->connect_ind)
						pops->connect_ind(cprot);
#endif /* CONFIG_ISDN_X25 */
				/* ppp needs to do negotiations first */
				if (lp->p_encap != ISDN_NET_ENCAP_SYNCPPP)
					isdn_net_device_wake_queue(lp);
				return 1;
			}
			break;
		case ISDN_STAT_NODCH:
			/* No D-Channel avail. */
			if (lp->dialstate == 4) {
				lp->dialstate--;
				return 1;
			}
			break;
		case ISDN_STAT_CINF:
			/* Charge-info from TelCo. Calculate interval between
			 * charge-infos and set timestamp for last info for
			 * usage by isdn_net_autohup()
			 */
			lp->charge++;
			if (lp->hupflags & ISDN_HAVECHARGE) {
				lp->hupflags &= ~ISDN_WAITCHARGE;
				lp->chargeint = jiffies - lp->chargetime - (2 * HZ);
			}
			if (lp->hupflags & ISDN_WAITCHARGE)
				lp->hupflags |= ISDN_HAVECHARGE;
			lp->chargetime = jiffies;
			printk(KERN_DEBUG "isdn_net: Got CINF chargetime of %s now %lu\n",
			       p->dev->name, lp->chargetime);
			return 1;
		}
