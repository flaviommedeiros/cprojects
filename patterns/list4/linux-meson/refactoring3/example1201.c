switch (TX4938_REV_PCODE()) {
#ifdef CONFIG_TOSHIBA_RBTX4927
	case 0x4927:
		txx9_board_vec = &rbtx4927_vec;
		break;
	case 0x4937:
		txx9_board_vec = &rbtx4937_vec;
		break;
#endif
#ifdef CONFIG_TOSHIBA_RBTX4938
	case 0x4938:
		txx9_board_vec = &rbtx4938_vec;
		break;
#endif
#ifdef CONFIG_TOSHIBA_RBTX4939
	case 0x4939:
		txx9_board_vec = &rbtx4939_vec;
		break;
#endif
	}
