switch (nType) {
	case typeSingle:
		nRc = SingleCPDO(&roundData, opcode, rFd);
		break;
	case typeDouble:
		nRc = DoubleCPDO(&roundData, opcode, rFd);
		break;
#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		nRc = ExtendedCPDO(&roundData, opcode, rFd);
		break;
#endif
	default:
		nRc = 0;
	}
