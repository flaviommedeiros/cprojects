switch (card->l2_proto[a - 1]) {
			case ISDN_PROTO_L2_X75I:
				sprintf(cbuf, "%02d;BX75\n", (int) a);
				break;
#ifdef CONFIG_ISDN_X25
			case ISDN_PROTO_L2_X25DTE:
				sprintf(cbuf, "%02d;BX2T\n", (int) a);
				break;
			case ISDN_PROTO_L2_X25DCE:
				sprintf(cbuf, "%02d;BX2C\n", (int) a);
				break;
#endif
			case ISDN_PROTO_L2_HDLC:
				sprintf(cbuf, "%02d;BTRA\n", (int) a);
				break;
			}
