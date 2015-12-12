switch (id) {
		case 1:		start = 0;	break;
		case 8:		start = 1;	break;
		case 5:		start = 2;	break;
		case 6:		start = 3;	break;
		case 25:	start = 4;	break;
#ifdef CONFIG_ENABLE_TTY_CIQ
		case 9:	        start = 5;	break;
		case 26:	start = 6;	break;
#endif
		default:	start = 0;
	}
