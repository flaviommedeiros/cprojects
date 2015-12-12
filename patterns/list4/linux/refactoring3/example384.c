switch (zone) {
	case ZONE_DMA:
		flag |= GFP_DMA;
		break;
#ifdef CONFIG_ZONE_DMA32
	case ZONE_DMA32:
		flag |= GFP_DMA32;
		break;
#endif
	}
