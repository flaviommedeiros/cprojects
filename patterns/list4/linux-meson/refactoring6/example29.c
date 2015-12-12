if ((info->online > 1)
#ifdef CONFIG_ISDN_AUDIO
		    || (info->vonline & 3)
#endif
			) {
#ifdef CONFIG_ISDN_AUDIO
			if (!info->vonline)
#endif
				isdn_tty_check_esc(buf, m->mdmreg[REG_ESC], c,
						   &(m->pluscount),
						   &(m->lastplus));
			memcpy(&info->port.xmit_buf[info->xmit_count], buf, c);
#ifdef CONFIG_ISDN_AUDIO
			if (info->vonline) {
				int cc = isdn_tty_handleDLEdown(info, m, c);
				if (info->vonline & 2) {
					if (!cc) {
						/* If DLE decoding results in zero-transmit, but
						 * c originally was non-zero, do a wakeup.
						 */
						tty_wakeup(tty);
						info->msr |= UART_MSR_CTS;
						info->lsr |= UART_LSR_TEMT;
					}
					info->xmit_count += cc;
				}
				if ((info->vonline & 3) == 1) {
					/* Do NOT handle Ctrl-Q or Ctrl-S
					 * when in full-duplex audio mode.
					 */
					if (isdn_tty_end_vrx(buf, c)) {
						info->vonline &= ~1;
#ifdef ISDN_DEBUG_MODEM_VOICE
						printk(KERN_DEBUG
						       "got !^Q/^S, send DLE-ETX,VCON on ttyI%d\n",
						       info->line);
#endif
						isdn_tty_at_cout("\020\003\r\nVCON\r\n", info);
					}
				}
			} else
				if (TTY_IS_FCLASS1(info)) {
					int cc = isdn_tty_handleDLEdown(info, m, c);

					if (info->vonline & 4) { /* ETX seen */
						isdn_ctrl c;

						c.command = ISDN_CMD_FAXCMD;
						c.driver = info->isdn_driver;
						c.arg = info->isdn_channel;
						c.parm.aux.cmd = ISDN_FAX_CLASS1_CTRL;
						c.parm.aux.subcmd = ETX;
						isdn_command(&c);
					}
					info->vonline = 0;
#ifdef ISDN_DEBUG_MODEM_VOICE
					printk(KERN_DEBUG "fax dle cc/c %d/%d\n", cc, c);
#endif
					info->xmit_count += cc;
				} else
#endif
					info->xmit_count += c;
		} else {
			info->msr |= UART_MSR_CTS;
			info->lsr |= UART_LSR_TEMT;
			if (info->dialing) {
				info->dialing = 0;
#ifdef ISDN_DEBUG_MODEM_HUP
				printk(KERN_DEBUG "Mhup in isdn_tty_write\n");
#endif
				isdn_tty_modem_result(RESULT_NO_CARRIER, info);
				isdn_tty_modem_hup(info, 1);
			} else
				c = isdn_tty_edit_at(buf, c, info);
		}
