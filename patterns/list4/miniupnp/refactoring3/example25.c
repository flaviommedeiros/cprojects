switch(opcode) {
	case PCP_OPCODE_ANNOUNCE:
		return "ANNOUNCE";
	case PCP_OPCODE_MAP:
		return "MAP";
	case PCP_OPCODE_PEER:
		return "PEER";
#ifdef  PCP_SADSCP
	case PCP_OPCODE_SADSCP:
		return "SADSCP";
#endif	/* PCP_SADSCP */
	default:
		return "UNKNOWN";
	}
