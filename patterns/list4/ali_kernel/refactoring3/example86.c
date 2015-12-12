switch(l2) {
			case ISDN_PROTO_L2_MODEM: 
				usg = ISDN_USAGE_MODEM;
				break;
#ifdef CONFIG_ISDN_TTY_FAX
			case ISDN_PROTO_L2_FAX: 
				usg = ISDN_USAGE_FAX;
				break;
#endif
			case ISDN_PROTO_L2_TRANS: 
			default:
				usg = ISDN_USAGE_VOICE;
				break;
		}
