switch (*p) {
			case ' ':
				p++;
				break;
			case 'A':
				/* A - Accept incoming call */
				p++;
				isdn_tty_cmd_ATA(info);
				return;
				break;
			case 'D':
				/* D - Dial */
				if (info->msr & UART_MSR_DCD)
					PARSE_ERROR;
				if (info->msr & UART_MSR_RI) {
					isdn_tty_modem_result(RESULT_NO_CARRIER, info);
					return;
				}
				isdn_tty_getdial(++p, ds, sizeof ds);
				p += strlen(p);
				if (!strlen(m->msn))
					isdn_tty_modem_result(RESULT_NO_MSN_EAZ, info);
				else if (strlen(ds))
					isdn_tty_dial(ds, info, m);
				else
					PARSE_ERROR;
				return;
			case 'E':
				/* E - Turn Echo on/off */
				p++;
				switch (isdn_getnum(&p)) {
					case 0:
						m->mdmreg[REG_ECHO] &= ~BIT_ECHO;
						break;
					case 1:
						m->mdmreg[REG_ECHO] |= BIT_ECHO;
						break;
					default:
						PARSE_ERROR;
				}
				break;
			case 'H':
				/* H - On/Off-hook */
				p++;
				switch (*p) {
					case '0':
						p++;
						isdn_tty_on_hook(info);
						break;
					case '1':
						p++;
						isdn_tty_off_hook();
						break;
					default:
						isdn_tty_on_hook(info);
						break;
				}
				break;
			case 'I':
				/* I - Information */
				p++;
				isdn_tty_at_cout("\r\nLinux ISDN", info);
				switch (*p) {
					case '0':
					case '1':
						p++;
						break;
					case '2':
						p++;
						isdn_tty_report(info);
						break;
					case '3':
                                                p++;
                                                sprintf(ds, "\r\n%d", info->emu.charge);
                                                isdn_tty_at_cout(ds, info);
                                                break;
					default:;
				}
				break;
#ifdef DUMMY_HAYES_AT
			case 'L':
			case 'M':
				/* only for be compilant with common scripts */
				/* no function */
				p++;
				isdn_getnum(&p);
				break;
#endif
			case 'O':
				/* O - Go online */
				p++;
				if (info->msr & UART_MSR_DCD)
					/* if B-Channel is up */
					isdn_tty_modem_result((m->mdmreg[REG_L2PROT] == ISDN_PROTO_L2_MODEM) ? RESULT_CONNECT:RESULT_CONNECT64000, info);
				else
					isdn_tty_modem_result(RESULT_NO_CARRIER, info);
				return;
			case 'Q':
				/* Q - Turn Emulator messages on/off */
				p++;
				switch (isdn_getnum(&p)) {
					case 0:
						m->mdmreg[REG_RESP] |= BIT_RESP;
						break;
					case 1:
						m->mdmreg[REG_RESP] &= ~BIT_RESP;
						break;
					default:
						PARSE_ERROR;
				}
				break;
			case 'S':
				/* S - Set/Get Register */
				p++;
				if (isdn_tty_cmd_ATS(&p, info))
					return;
				break;
			case 'V':
				/* V - Numeric or ASCII Emulator-messages */
				p++;
				switch (isdn_getnum(&p)) {
					case 0:
						m->mdmreg[REG_RESP] |= BIT_RESPNUM;
						break;
					case 1:
						m->mdmreg[REG_RESP] &= ~BIT_RESPNUM;
						break;
					default:
						PARSE_ERROR;
				}
				break;
			case 'Z':
				/* Z - Load Registers from Profile */
				p++;
				if (info->msr & UART_MSR_DCD) {
					info->online = 0;
					isdn_tty_on_hook(info);
				}
				isdn_tty_modem_reset_regs(info, 1);
				break;
			case '+':
				p++;
				switch (*p) {
#ifdef CONFIG_ISDN_AUDIO
					case 'F':
						p++;
						if (isdn_tty_cmd_PLUSF(&p, info))
							return;
						break;
					case 'V':
						if ((!(m->mdmreg[REG_SI1] & 1)) ||
							(m->mdmreg[REG_L2PROT] == ISDN_PROTO_L2_MODEM))
							PARSE_ERROR;
						p++;
						if (isdn_tty_cmd_PLUSV(&p, info))
							return;
						break;
#endif                          /* CONFIG_ISDN_AUDIO */
					case 'S':	/* SUSPEND */
						p++;
						isdn_tty_get_msnstr(ds, &p);
						isdn_tty_suspend(ds, info, m);
						break;
					case 'R':	/* RESUME */
						p++;
						isdn_tty_get_msnstr(ds, &p);
						isdn_tty_resume(ds, info, m);
						break;
					case 'M':	/* MESSAGE */
						p++;
						isdn_tty_send_msg(info, m, p);
						break;
					default:
						PARSE_ERROR;
				}
				break;
			case '&':
				p++;
				if (isdn_tty_cmd_ATand(&p, info))
					return;
				break;
			default:
				PARSE_ERROR;
		}
