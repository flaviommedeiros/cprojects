switch (opcode & 0xf0) {
#ifdef CONFIG_X86_64
	case 0x40:
		goto retry; /* REX prefix is boostable */
#endif
	case 0x60:
		if (0x63 < opcode && opcode < 0x67)
			goto retry; /* prefixes */
		/* can't boost Address-size override and bound */
		return (opcode != 0x62 && opcode != 0x67);
	case 0x70:
		return 0; /* can't boost conditional jump */
	case 0xc0:
		/* can't boost software-interruptions */
		return (0xc1 < opcode && opcode < 0xcc) || opcode == 0xcf;
	case 0xd0:
		/* can boost AA* and XLAT */
		return (opcode == 0xd4 || opcode == 0xd5 || opcode == 0xd7);
	case 0xe0:
		/* can boost in/out and absolute jmps */
		return ((opcode & 0x04) || opcode == 0xea);
	case 0xf0:
		if ((opcode & 0x0c) == 0 && opcode != 0xf1)
			goto retry; /* lock/rep(ne) prefix */
		/* clear and set flags are boostable */
		return (opcode == 0xf5 || (0xf7 < opcode && opcode < 0xfe));
	default:
		/* segment override prefixes are boostable */
		if (opcode == 0x26 || opcode == 0x36 || opcode == 0x3e)
			goto retry; /* prefixes */
		/* CS override prefix and call are not boostable */
		return (opcode != 0x2e && opcode != 0x9a);
	}
