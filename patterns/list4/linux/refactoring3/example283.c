switch (depth) {
	case 8:
		size = ARRAY_SIZE(bios8);
		mode = bios8;
		break;
	case 16:
		size = ARRAY_SIZE(bios16);
		mode = bios16;
		break;
	case 24:
		size = ARRAY_SIZE(bios24);
		mode = bios24;
		break;
#ifdef NO_32BIT_SUPPORT_YET
	case 32:
		size = ARRAY_SIZE(bios32);
		mode = bios32;
		break;
#endif
	default:
		return 0;
	}
