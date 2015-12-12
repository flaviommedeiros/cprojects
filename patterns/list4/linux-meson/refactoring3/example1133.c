switch (opcode & MASK_TRANSFER_LENGTH) {
	case TRANSFER_SINGLE:
		storeSingle(&roundData, getFd(opcode), pAddress);
		break;
	case TRANSFER_DOUBLE:
		storeDouble(&roundData, getFd(opcode), pAddress);
		break;
#ifdef CONFIG_FPE_NWFPE_XP
	case TRANSFER_EXTENDED:
		storeExtended(getFd(opcode), pAddress);
		break;
#endif
	default:
		nRc = 0;
	}
