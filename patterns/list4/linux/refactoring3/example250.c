switch (size) {
#ifdef CONFIG_64BIT
	case 8:
		writeq_relaxed(*(u64 *)payload, dest);
		break;
#endif
	case 4:
		writel_relaxed(*(u32 *)payload, dest);
		break;
	case 2:
		writew_relaxed(*(u16 *)payload, dest);
		break;
	case 1:
		writeb_relaxed(*(u8 *)payload, dest);
		break;
	default:
		break;
	}
