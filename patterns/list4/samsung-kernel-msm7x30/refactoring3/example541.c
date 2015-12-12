switch(basechipid) {
#ifdef CONFIG_FB_SIS_300
	case SIS_540:	nbridgeidx = 0; nbridgenum = 1; break;
	case SIS_630:	nbridgeidx = 1; nbridgenum = 2; break;
#endif
#ifdef CONFIG_FB_SIS_315
	case SIS_550:   nbridgeidx = 3; nbridgenum = 1; break;
	case SIS_650:	nbridgeidx = 4; nbridgenum = 3; break;
	case SIS_660:	nbridgeidx = 7; nbridgenum = 5; break;
#endif
	default:	return NULL;
	}
