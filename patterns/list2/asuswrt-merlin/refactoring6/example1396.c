if (
#ifndef FIX_FILE_TRANSFER
				(info->flags & ISDN_ASYNC_NORMAL_ACTIVE) &&
#endif
				(info->isdn_driver == -1) &&
				(info->isdn_channel == -1) &&
				(USG_NONE(dev->usage[idx]))) {
				int matchret;

				if ((matchret = isdn_tty_match_icall(eaz, &info->emu, di)) > wret)
					wret = matchret;
				if (!matchret) {                  /* EAZ is matching */
					info->isdn_driver = di;
					info->isdn_channel = ch;
					info->drv_index = idx;
					dev->m_idx[idx] = info->line;
					dev->usage[idx] &= ISDN_USAGE_EXCLUSIVE;
					dev->usage[idx] |= isdn_calc_usage(si1, info->emu.mdmreg[REG_L2PROT]); 
					strcpy(dev->num[idx], nr);
					strcpy(info->emu.cpn, eaz);
					info->emu.mdmreg[REG_SI1I] = si2bit[si1];
					info->emu.mdmreg[REG_PLAN] = setup->plan;
					info->emu.mdmreg[REG_SCREEN] = setup->screen;
					isdn_info_update();
					spin_unlock_irqrestore(&dev->lock, flags);
					printk(KERN_INFO "isdn_tty: call from %s, -> RING on ttyI%d\n", nr,
					       info->line);
					info->msr |= UART_MSR_RI;
					isdn_tty_modem_result(RESULT_RING, info);
					isdn_timer_ctrl(ISDN_TIMER_MODEMRING, 1);
					return 1;
				}
			}
