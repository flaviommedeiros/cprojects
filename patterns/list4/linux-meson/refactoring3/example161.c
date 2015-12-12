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
