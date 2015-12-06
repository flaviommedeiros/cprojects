switch (type) {
		default:
		case ONEBYTE:
			indextable = index_x86DisassemblerOneByteOpcodes;
			index = indextable[insnContext];
			if (index)
				dec = &ONEBYTE_SYM[index - 1].modRMDecisions[opcode];
			else
				dec = &emptyTable.modRMDecisions[opcode];
			break;
		case TWOBYTE:
			indextable = index_x86DisassemblerTwoByteOpcodes;
			index = indextable[insnContext];
			if (index)
				dec = &TWOBYTE_SYM[index - 1].modRMDecisions[opcode];
			else
				dec = &emptyTable.modRMDecisions[opcode];
			break;
		case THREEBYTE_38:
			indextable = index_x86DisassemblerThreeByte38Opcodes;
			index = indextable[insnContext];
			if (index)
				dec = &THREEBYTE38_SYM[index - 1].modRMDecisions[opcode];
			else
				dec = &emptyTable.modRMDecisions[opcode];
			break;
		case THREEBYTE_3A:
			indextable = index_x86DisassemblerThreeByte3AOpcodes;
			index = indextable[insnContext];
			if (index)
				dec = &THREEBYTE3A_SYM[index - 1].modRMDecisions[opcode];
			else
				dec = &emptyTable.modRMDecisions[opcode];
			break;
#ifndef CAPSTONE_X86_REDUCE
		case XOP8_MAP:
			indextable = index_x86DisassemblerXOP8Opcodes;
			index = indextable[insnContext];
			if (index)
				dec = &XOP8_MAP_SYM[index - 1].modRMDecisions[opcode];
			else
				dec = &emptyTable.modRMDecisions[opcode];
			break;
		case XOP9_MAP:
			indextable = index_x86DisassemblerXOP9Opcodes;
			index = indextable[insnContext];
			if (index)
				dec = &XOP9_MAP_SYM[index - 1].modRMDecisions[opcode];
			else
				dec = &emptyTable.modRMDecisions[opcode];
			break;
		case XOPA_MAP:
			indextable = index_x86DisassemblerXOPAOpcodes;
			index = indextable[insnContext];
			if (index)
				dec = &XOPA_MAP_SYM[index - 1].modRMDecisions[opcode];
			else
				dec = &emptyTable.modRMDecisions[opcode];
			break;
		case T3DNOW_MAP:
			indextable = index_x86DisassemblerT3DNOWOpcodes;
			index = indextable[insnContext];
			if (index)
				dec = &T3DNOW_MAP_SYM[index - 1].modRMDecisions[opcode];
			else
				dec = &emptyTable.modRMDecisions[opcode];
			break;
#endif
	}
