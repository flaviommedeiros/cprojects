switch (dev->id) {
		case 1:		index = 0;	break;
		case 8:		index = 1;	break;
		case 5:		index = 2;	break;
		case 6:		index = 3;	break;
		case 25:	index = 4;	break;
#ifdef CONFIG_ENABLE_TTY_CIQ
		case 9:	        index = 5;	break;
		case 26:	index = 6;	break;
#endif
		default:	index = 0;
	}
