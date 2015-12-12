switch (a >> 8) {
						case ISDN_PROTO_L2_X75I:
							sprintf(cbuf, "%02d;BX75\n", (int) (a & 255) + 1);
							break;
#ifdef CONFIG_ISDN_X25
						case ISDN_PROTO_L2_X25DTE:
							sprintf(cbuf, "%02d;BX2T\n", (int) (a & 255) + 1);
							break;
						case ISDN_PROTO_L2_X25DCE:
							sprintf(cbuf, "%02d;BX2C\n", (int) (a & 255) + 1);
							break;
#endif
						case ISDN_PROTO_L2_HDLC:
							sprintf(cbuf, "%02d;BTRA\n", (int) (a & 255) + 1);
							break;
						case ISDN_PROTO_L2_TRANS:
							sprintf(cbuf, "%02d;BTRA\n", (int) (a & 255) + 1);
							break;
						default:
							return -EINVAL;
					}
