switch (standard) {
	case DRX_STANDARD_8VSB:
		cmd_scu.command = SCU_RAM_COMMAND_STANDARD_VSB |
		    SCU_RAM_COMMAND_CMD_DEMOD_GET_LOCK;
		demod_lock |= 0x6;
		break;
#ifndef DRXJ_VSB_ONLY
	case DRX_STANDARD_ITU_A:
	case DRX_STANDARD_ITU_B:
	case DRX_STANDARD_ITU_C:
		cmd_scu.command = SCU_RAM_COMMAND_STANDARD_QAM |
		    SCU_RAM_COMMAND_CMD_DEMOD_GET_LOCK;
		break;
#endif
	case DRX_STANDARD_UNKNOWN:	/* fallthrough */
	default:
		return -EIO;
	}
