switch (reg_size) {
	case 1:
		return *(u8 *)reg;
	case 2:
		return *(u16 *)reg;
	case 4:
		return *(u32 *)reg;
#ifdef CONFIG_64BIT
	case 8:
		return *(u64 *)reg;
#endif
	default:
		BUG();
	}
