switch (*p[0]) {
		case 'B':
			/* &B - Set Buffersize */
			p[0]++;
			i = isdn_getnum(p);
			if ((i < 0) || (i > ISDN_SERIAL_XMIT_MAX))
				PARSE_ERROR1;
#ifdef CONFIG_ISDN_AUDIO
			if ((m->mdmreg[REG_SI1] & 1) && (i > VBUF))
				PARSE_ERROR1;
#endif
			m->mdmreg[REG_PSIZE] = i / 16;
			info->xmit_size = m->mdmreg[REG_PSIZE] * 16;
			switch (m->mdmreg[REG_L2PROT]) {
				case ISDN_PROTO_L2_V11096:
				case ISDN_PROTO_L2_V11019:
				case ISDN_PROTO_L2_V11038:
					info->xmit_size /= 10;		
			}
			break;
		case 'C':
			/* &C - DCD Status */
			p[0]++;
			switch (isdn_getnum(p)) {
				case 0:
					m->mdmreg[REG_DCD] &= ~BIT_DCD;
					break;
				case 1:
					m->mdmreg[REG_DCD] |= BIT_DCD;
					break;
				default:
					PARSE_ERROR1
			}
			break;
		case 'D':
			/* &D - Set DTR-Low-behavior */
			p[0]++;
			switch (isdn_getnum(p)) {
				case 0:
					m->mdmreg[REG_DTRHUP] &= ~BIT_DTRHUP;
					m->mdmreg[REG_DTRR] &= ~BIT_DTRR;
					break;
				case 2:
					m->mdmreg[REG_DTRHUP] |= BIT_DTRHUP;
					m->mdmreg[REG_DTRR] &= ~BIT_DTRR;
					break;
				case 3:
					m->mdmreg[REG_DTRHUP] |= BIT_DTRHUP;
					m->mdmreg[REG_DTRR] |= BIT_DTRR;
					break;
				default:
					PARSE_ERROR1
			}
			break;
		case 'E':
			/* &E -Set EAZ/MSN */
			p[0]++;
			isdn_tty_get_msnstr(m->msn, p);
			break;
		case 'F':
			/* &F -Set Factory-Defaults */
			p[0]++;
			if (info->msr & UART_MSR_DCD)
				PARSE_ERROR1;
			isdn_tty_reset_profile(m);
			isdn_tty_modem_reset_regs(info, 1);
			break;
#ifdef DUMMY_HAYES_AT
		case 'K':
			/* only for be compilant with common scripts */
			/* &K Flowcontrol - no function */
			p[0]++;
			isdn_getnum(p);
			break;
#endif
		case 'L':
			/* &L -Set Numbers to listen on */
			p[0]++;
			i = 0;
			while (*p[0] && (strchr("0123456789,-*[]?;", *p[0])) &&
			       (i < ISDN_LMSNLEN - 1))
				m->lmsn[i++] = *p[0]++;
			m->lmsn[i] = '\0';
			break;
		case 'R':
			/* &R - Set V.110 bitrate adaption */
			p[0]++;
			i = isdn_getnum(p);
			switch (i) {
				case 0:
					/* Switch off V.110, back to X.75 */
					m->mdmreg[REG_L2PROT] = ISDN_PROTO_L2_X75I;
					m->mdmreg[REG_SI2] = 0;
					info->xmit_size = m->mdmreg[REG_PSIZE] * 16;
					break;
				case 9600:
					m->mdmreg[REG_L2PROT] = ISDN_PROTO_L2_V11096;
					m->mdmreg[REG_SI2] = 197;
					info->xmit_size = m->mdmreg[REG_PSIZE] * 16 / 10;
					break;
				case 19200:
					m->mdmreg[REG_L2PROT] = ISDN_PROTO_L2_V11019;
					m->mdmreg[REG_SI2] = 199;
					info->xmit_size = m->mdmreg[REG_PSIZE] * 16 / 10;
					break;
				case 38400:
					m->mdmreg[REG_L2PROT] = ISDN_PROTO_L2_V11038;
					m->mdmreg[REG_SI2] = 198; /* no existing standard for this */
					info->xmit_size = m->mdmreg[REG_PSIZE] * 16 / 10;
					break;
				default:
					PARSE_ERROR1;
			}
			/* Switch off T.70 */
			m->mdmreg[REG_T70] &= ~(BIT_T70 | BIT_T70_EXT);
			/* Set Service 7 */
			m->mdmreg[REG_SI1] |= 4;
			break;
		case 'S':
			/* &S - Set Windowsize */
			p[0]++;
			i = isdn_getnum(p);
			if ((i > 0) && (i < 9))
				m->mdmreg[REG_WSIZE] = i;
			else
				PARSE_ERROR1;
			break;
		case 'V':
			/* &V - Show registers */
			p[0]++;
			isdn_tty_at_cout("\r\n", info);
			for (i = 0; i < ISDN_MODEM_NUMREG; i++) {
				sprintf(rb, "S%02d=%03d%s", i,
					m->mdmreg[i], ((i + 1) % 10) ? " " : "\r\n");
				isdn_tty_at_cout(rb, info);
			}
			sprintf(rb, "\r\nEAZ/MSN: %.50s\r\n",
				strlen(m->msn) ? m->msn : "None");
			isdn_tty_at_cout(rb, info);
			if (strlen(m->lmsn)) {
				isdn_tty_at_cout("\r\nListen: ", info);
				isdn_tty_at_cout(m->lmsn, info);
				isdn_tty_at_cout("\r\n", info);
			}
			break;
		case 'W':
			/* &W - Write Profile */
			p[0]++;
			switch (*p[0]) {
				case '0':
					p[0]++;
					modem_write_profile(m);
					break;
				default:
					PARSE_ERROR1;
			}
			break;
		case 'X':
			/* &X - Switch to BTX-Mode and T.70 */
			p[0]++;
			switch (isdn_getnum(p)) {
				case 0:
					m->mdmreg[REG_T70] &= ~(BIT_T70 | BIT_T70_EXT);
					info->xmit_size = m->mdmreg[REG_PSIZE] * 16;
					break;
				case 1:
					m->mdmreg[REG_T70] |= BIT_T70;
					m->mdmreg[REG_T70] &= ~BIT_T70_EXT;
					m->mdmreg[REG_L2PROT] = ISDN_PROTO_L2_X75I;
					info->xmit_size = 112;
					m->mdmreg[REG_SI1] = 4;
					m->mdmreg[REG_SI2] = 0;
					break;
				case 2:
					m->mdmreg[REG_T70] |= (BIT_T70 | BIT_T70_EXT);
					m->mdmreg[REG_L2PROT] = ISDN_PROTO_L2_X75I;
					info->xmit_size = 112;
					m->mdmreg[REG_SI1] = 4;
					m->mdmreg[REG_SI2] = 0;
					break;
				default:
					PARSE_ERROR1;
			}
			break;
		default:
			PARSE_ERROR1;
	}
