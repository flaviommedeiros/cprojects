switch (c->command) {
                        case ISDN_STAT_CINF:
                                printk(KERN_DEBUG "CHARGEINFO on ttyI%d: %ld %s\n", info->line, c->arg, c->parm.num);
                                info->emu.charge = (unsigned) simple_strtoul(c->parm.num, &e, 10);
                                if (e == (char *)c->parm.num)
					info->emu.charge = 0;
				
                                break;			
			case ISDN_STAT_BSENT:
#ifdef ISDN_TTY_STAT_DEBUG
				printk(KERN_DEBUG "tty_STAT_BSENT ttyI%d\n", info->line);
#endif
				if ((info->isdn_driver == c->driver) &&
				    (info->isdn_channel == c->arg)) {
					info->msr |= UART_MSR_CTS;
					if (info->send_outstanding)
						if (!(--info->send_outstanding))
							info->lsr |= UART_LSR_TEMT;
					isdn_tty_tint(info);
					return 1;
				}
				break;
			case ISDN_STAT_CAUSE:
#ifdef ISDN_TTY_STAT_DEBUG
				printk(KERN_DEBUG "tty_STAT_CAUSE ttyI%d\n", info->line);
#endif
				/* Signal cause to tty-device */
				strncpy(info->last_cause, c->parm.num, 5);
				return 1;
			case ISDN_STAT_DISPLAY:
#ifdef ISDN_TTY_STAT_DEBUG
				printk(KERN_DEBUG "tty_STAT_DISPLAY ttyI%d\n", info->line);
#endif
				/* Signal display to tty-device */
				if ((info->emu.mdmreg[REG_DISPLAY] & BIT_DISPLAY) && 
					!(info->emu.mdmreg[REG_RESPNUM] & BIT_RESPNUM)) {
				  isdn_tty_at_cout("\r\n", info);
				  isdn_tty_at_cout("DISPLAY: ", info);
				  isdn_tty_at_cout(c->parm.display, info);
				  isdn_tty_at_cout("\r\n", info);
				}
				return 1;
			case ISDN_STAT_DCONN:
#ifdef ISDN_TTY_STAT_DEBUG
				printk(KERN_DEBUG "tty_STAT_DCONN ttyI%d\n", info->line);
#endif
				if (TTY_IS_ACTIVE(info)) {
					if (info->dialing == 1) {
						info->dialing = 2;
						return 1;
					}
				}
				break;
			case ISDN_STAT_DHUP:
#ifdef ISDN_TTY_STAT_DEBUG
				printk(KERN_DEBUG "tty_STAT_DHUP ttyI%d\n", info->line);
#endif
				if (TTY_IS_ACTIVE(info)) {
					if (info->dialing == 1) 
						isdn_tty_modem_result(RESULT_BUSY, info);
					if (info->dialing > 1) 
						isdn_tty_modem_result(RESULT_NO_CARRIER, info);
					info->dialing = 0;
#ifdef ISDN_DEBUG_MODEM_HUP
					printk(KERN_DEBUG "Mhup in ISDN_STAT_DHUP\n");
#endif
					isdn_tty_modem_hup(info, 0);
					return 1;
				}
				break;
			case ISDN_STAT_BCONN:
#ifdef ISDN_TTY_STAT_DEBUG
				printk(KERN_DEBUG "tty_STAT_BCONN ttyI%d\n", info->line);
#endif
				/* Wake up any processes waiting
				 * for incoming call of this device when
				 * DCD follow the state of incoming carrier
				 */
				if (info->blocked_open &&
				   (info->emu.mdmreg[REG_DCD] & BIT_DCD)) {
					wake_up_interruptible(&info->open_wait);
				}

				/* Schedule CONNECT-Message to any tty
				 * waiting for it and
				 * set DCD-bit of its modem-status.
				 */
				if (TTY_IS_ACTIVE(info) ||
				    (info->blocked_open && (info->emu.mdmreg[REG_DCD] & BIT_DCD))) {
					info->msr |= UART_MSR_DCD;
					info->emu.charge = 0;
					if (info->dialing & 0xf)
						info->last_dir = 1;
					else
						info->last_dir = 0;
					info->dialing = 0;
					info->rcvsched = 1;
					if (USG_MODEM(dev->usage[i])) {
						if (info->emu.mdmreg[REG_L2PROT] == ISDN_PROTO_L2_MODEM) {
							strcpy(info->emu.connmsg, c->parm.num);
							isdn_tty_modem_result(RESULT_CONNECT, info);
						} else
							isdn_tty_modem_result(RESULT_CONNECT64000, info);
					}
					if (USG_VOICE(dev->usage[i]))
						isdn_tty_modem_result(RESULT_VCON, info);
					return 1;
				}
				break;
			case ISDN_STAT_BHUP:
#ifdef ISDN_TTY_STAT_DEBUG
				printk(KERN_DEBUG "tty_STAT_BHUP ttyI%d\n", info->line);
#endif
				if (TTY_IS_ACTIVE(info)) {
#ifdef ISDN_DEBUG_MODEM_HUP
					printk(KERN_DEBUG "Mhup in ISDN_STAT_BHUP\n");
#endif
					isdn_tty_modem_hup(info, 0);
					return 1;
				}
				break;
			case ISDN_STAT_NODCH:
#ifdef ISDN_TTY_STAT_DEBUG
				printk(KERN_DEBUG "tty_STAT_NODCH ttyI%d\n", info->line);
#endif
				if (TTY_IS_ACTIVE(info)) {
					if (info->dialing) {
						info->dialing = 0;
						info->last_l2 = -1;
						info->last_si = 0;
						sprintf(info->last_cause, "0000");
						isdn_tty_modem_result(RESULT_NO_DIALTONE, info);
					}
					isdn_tty_modem_hup(info, 0);
					return 1;
				}
				break;
			case ISDN_STAT_UNLOAD:
#ifdef ISDN_TTY_STAT_DEBUG
				printk(KERN_DEBUG "tty_STAT_UNLOAD ttyI%d\n", info->line);
#endif
				for (i = 0; i < ISDN_MAX_CHANNELS; i++) {
					info = &dev->mdm.info[i];
					if (info->isdn_driver == c->driver) {
						if (info->online)
							isdn_tty_modem_hup(info, 1);
					}
				}
				return 1;
#ifdef CONFIG_ISDN_TTY_FAX
			case ISDN_STAT_FAXIND:
				if (TTY_IS_ACTIVE(info)) {
					isdn_tty_fax_command(info, c); 
				}
				break;
#endif
#ifdef CONFIG_ISDN_AUDIO
			case ISDN_STAT_AUDIO:
				if (TTY_IS_ACTIVE(info)) {
					switch(c->parm.num[0]) {
						case ISDN_AUDIO_DTMF:
							if (info->vonline) {
								isdn_audio_put_dle_code(info,
									c->parm.num[1]);
							}
							break;
					}
				}
				break;
#endif
		}
