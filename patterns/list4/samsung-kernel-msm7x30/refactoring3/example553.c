switch(SiS_Pr->SiS_LCDResInfo) {
	case Panel_640x480:   tempbx = 12; break;
	case Panel_320x240_1: tempbx = 10; break;
	case Panel_320x240_2:
	case Panel_320x240_3: tempbx = 14; break;
	case Panel_800x600:   tempbx = 16; break;
	case Panel_1024x600:  tempbx = 18; break;
	case Panel_1152x768:
	case Panel_1024x768:  tempbx = 20; break;
	case Panel_1280x768:  tempbx = 22; break;
	case Panel_1280x1024: tempbx = 24; break;
	case Panel_1400x1050: tempbx = 26; break;
	case Panel_1600x1200: tempbx = 28; break;
#ifdef CONFIG_FB_SIS_300
	case Panel_Barco1366: tempbx = 80; break;
#endif
	}
