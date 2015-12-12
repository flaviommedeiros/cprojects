switch (reg_size) {
	case 1:
	case 2:
	case 4:
#ifdef CONFIG_64BIT
	case 8:
#endif
		break;
	default:
		BUG();
	}
