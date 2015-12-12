switch (opcode8) {
		case REPE_PREFIX_OPCODE:
		case REPNE_PREFIX_OPCODE:
		case LOCK_PREFIX_OPCODE:
		case CS_PREFIX_OPCODE:
		case SS_PREFIX_OPCODE:
		case DS_PREFIX_OPCODE:
		case ES_PREFIX_OPCODE:
		case FS_PREFIX_OPCODE:
		case GS_PREFIX_OPCODE:
		case DATA_PREFIX_OPCODE:
		case ADDR_PREFIX_OPCODE:
#ifndef CONFIG_X86_32
		case 0x40 ... 0x4f:
#endif
			break;
		default:
			goto out_prefixes;
		}
