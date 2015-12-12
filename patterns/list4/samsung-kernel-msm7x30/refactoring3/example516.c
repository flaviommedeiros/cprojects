switch (type) {
		case LIRC_HOMEBREW:
		case LIRC_IGOR:
#ifdef CONFIG_LIRC_SERIAL_NSLU2
		case LIRC_NSLU2:
#endif
			hardware[type].features &=
				~(LIRC_CAN_SET_SEND_DUTY_CYCLE|
				  LIRC_CAN_SET_SEND_CARRIER);
			break;
		}
