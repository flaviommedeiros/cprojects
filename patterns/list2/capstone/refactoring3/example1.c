switch (type) {
		default:
		case ONEBYTE:
			decision = ONEBYTE_SYM;
			indextable = index_x86DisassemblerOneByteOpcodes;
			break;
		case TWOBYTE:
			decision = TWOBYTE_SYM;
			indextable = index_x86DisassemblerTwoByteOpcodes;
			break;
		case THREEBYTE_38:
			decision = THREEBYTE38_SYM;
			indextable = index_x86DisassemblerThreeByte38Opcodes;
			break;
		case THREEBYTE_3A:
			decision = THREEBYTE3A_SYM;
			indextable = index_x86DisassemblerThreeByte3AOpcodes;
			break;
#ifndef CAPSTONE_X86_REDUCE
		case XOP8_MAP:
			decision = XOP8_MAP_SYM;
			indextable = index_x86DisassemblerXOP8Opcodes;
			break;
		case XOP9_MAP:
			decision = XOP9_MAP_SYM;
			indextable = index_x86DisassemblerXOP9Opcodes;
			break;
		case XOPA_MAP:
			decision = XOPA_MAP_SYM;
			indextable = index_x86DisassemblerXOPAOpcodes;
			break;
		case T3DNOW_MAP:
			// 3DNow instructions always have ModRM byte
			return true;
#endif
	}
