switch (info->var.bits_per_pixel) {
	case 8:
		par->CRTC[0x13] = info->var.xres_virtual >> 3;
		par->ExtCRTOffset = info->var.xres_virtual >> 11;
		par->ExtColorModeSelect = 0x11;
		break;
	case 16:
		par->CRTC[0x13] = info->var.xres_virtual >> 2;
		par->ExtCRTOffset = info->var.xres_virtual >> 10;
		par->ExtColorModeSelect = 0x13;
		break;
	case 24:
		par->CRTC[0x13] = (info->var.xres_virtual * 3) >> 3;
		par->ExtCRTOffset = (info->var.xres_virtual * 3) >> 11;
		par->ExtColorModeSelect = 0x14;
		break;
#ifdef NO_32BIT_SUPPORT_YET
	case 32:		/* FIXME: guessed values */
		par->CRTC[0x13] = info->var.xres_virtual >> 1;
		par->ExtCRTOffset = info->var.xres_virtual >> 9;
		par->ExtColorModeSelect = 0x15;
		break;
#endif
	default:
		break;
	}
