switch (tcflag) {
			case B57600:
				baudpart = 1;
				break;
#ifdef B76800
			case B76800:
				baudpart = 2;
				break;
#endif
			case B115200:
				baudpart = 3;
				break;
			case B230400:
				baudpart = 9;
				break;
			case B460800:
				baudpart = 11;
				break;
#ifdef B921600
			case B921600:
				baudpart = 12;
				break;
#endif
			default:
				baudpart = 0;
			}
