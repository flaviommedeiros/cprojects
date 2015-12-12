switch (opcode & MASK_TRANSFER_LENGTH) {
	case TRANSFER_SINGLE:
		loadSingle(getFd(opcode), pAddress);
		break;
	case TRANSFER_DOUBLE:
		loadDouble(getFd(opcode), pAddress);
		break;
#ifdef CONFIG_FPE_NWFPE_XP
	case TRANSFER_EXTENDED:
		loadExtended(getFd(opcode), pAddress);
		break;
#endif
	default:
		nRc = 0;
	}
