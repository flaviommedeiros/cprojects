switch (*p[0]) {
			case '0':
				p[0]++;
				m->mdmreg[REG_L2PROT] = ISDN_PROTO_L2_X75I;
				m->mdmreg[REG_L3PROT] = ISDN_PROTO_L3_TRANS;
				m->mdmreg[REG_SI1] = 4;
				info->xmit_size =
					m->mdmreg[REG_PSIZE] * 16;
				break;
#ifdef CONFIG_ISDN_TTY_FAX
			case '1':
				p[0]++;
				if (!(dev->global_features &
				      ISDN_FEATURE_L3_FCLASS1))
					PARSE_ERROR1;
				m->mdmreg[REG_SI1] = 1;
				m->mdmreg[REG_L2PROT] = ISDN_PROTO_L2_FAX;
				m->mdmreg[REG_L3PROT] = ISDN_PROTO_L3_FCLASS1;
				info->xmit_size =
					m->mdmreg[REG_PSIZE] * 16;
				break;
			case '2':
				p[0]++;
				if (!(dev->global_features &
				      ISDN_FEATURE_L3_FCLASS2))
					PARSE_ERROR1;
				m->mdmreg[REG_SI1] = 1;
				m->mdmreg[REG_L2PROT] = ISDN_PROTO_L2_FAX;
				m->mdmreg[REG_L3PROT] = ISDN_PROTO_L3_FCLASS2;
				info->xmit_size =
					m->mdmreg[REG_PSIZE] * 16;
				break;
#endif
			case '8':
				p[0]++;
				/* L2 will change on dialout with si=1 */
				m->mdmreg[REG_L2PROT] = ISDN_PROTO_L2_X75I;
				m->mdmreg[REG_L3PROT] = ISDN_PROTO_L3_TRANS;
				m->mdmreg[REG_SI1] = 5;
				info->xmit_size = VBUF;
				break;
			case '?':
				p[0]++;
				strcpy(rs, "\r\n0,");
#ifdef CONFIG_ISDN_TTY_FAX
				if (dev->global_features &
				    ISDN_FEATURE_L3_FCLASS1)
					strcat(rs, "1,");
				if (dev->global_features &
				    ISDN_FEATURE_L3_FCLASS2)
					strcat(rs, "2,");
#endif
				strcat(rs, "8");
				isdn_tty_at_cout(rs, info);
				break;
			default:
				PARSE_ERROR1;
			}
