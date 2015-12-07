switch (ast _ module_info.type) {
	case ASAP_TYPE_SAP_B:
		call_6502(ast, ast _ module_info.player, ast _ module_info.fastplay);
		break;
	case ASAP_TYPE_SAP_C:
#ifndef ASAP_ONLY_SAP
	case ASAP_TYPE_CMC:
	case ASAP_TYPE_CM3:
	case ASAP_TYPE_CMR:
	case ASAP_TYPE_CMS:
#endif
		call_6502(ast, ast _ module_info.player + 6, ast _ module_info.fastplay);
		break;
	case ASAP_TYPE_SAP_D:
		s = ast _ cpu_s;
#define PUSH_ON_6502_STACK(x)  dPutByte(0x100 + s, x); s = (s - 1) & 0xff
#define RETURN_FROM_PLAYER_ADDR  0xd200
		/* save 6502 state on 6502 stack */
		PUSH_ON_6502_STACK(ast _ cpu_pc >> 8);
		PUSH_ON_6502_STACK(ast _ cpu_pc & 0xff);
		PUSH_ON_6502_STACK(((ast _ cpu_nz | (ast _ cpu_nz >> 1)) & 0x80) + ast _ cpu_vdi + \
			((ast _ cpu_nz & 0xff) == 0 ? Z_FLAG : 0) + ast _ cpu_c + 0x20);
		PUSH_ON_6502_STACK(ast _ cpu_a);
		PUSH_ON_6502_STACK(ast _ cpu_x);
		PUSH_ON_6502_STACK(ast _ cpu_y);
		/* RTS will jump to 6502 code that restores the state */
		PUSH_ON_6502_STACK((RETURN_FROM_PLAYER_ADDR - 1) >> 8);
		PUSH_ON_6502_STACK((RETURN_FROM_PLAYER_ADDR - 1) & 0xff);
		ast _ cpu_s = s;
		dPutByte(RETURN_FROM_PLAYER_ADDR, 0x68);     /* PLA */
		dPutByte(RETURN_FROM_PLAYER_ADDR + 1, 0xa8); /* TAY */
		dPutByte(RETURN_FROM_PLAYER_ADDR + 2, 0x68); /* PLA */
		dPutByte(RETURN_FROM_PLAYER_ADDR + 3, 0xaa); /* TAX */
		dPutByte(RETURN_FROM_PLAYER_ADDR + 4, 0x68); /* PLA */
		dPutByte(RETURN_FROM_PLAYER_ADDR + 5, 0x40); /* RTI */
		ast _ cpu_pc = ast _ module_info.player;
		Cpu_RunScanlines(ast, ast _ module_info.fastplay);
		break;
	case ASAP_TYPE_SAP_S:
		Cpu_RunScanlines(ast, ast _ module_info.fastplay);
		{
			V(int, i) = dGetByte(0x45) - 1;
			dPutByte(0x45, i);
			if (i == 0)
				dPutByte(0xb07b, dGetByte(0xb07b) + 1);
		}
		break;
#ifndef ASAP_ONLY_SAP
	case ASAP_TYPE_DLT:
		call_6502(ast, ast _ module_info.player + 0x103, ast _ module_info.fastplay);
		break;
	case ASAP_TYPE_MPT:
	case ASAP_TYPE_RMT:
	case ASAP_TYPE_TM2:
		call_6502(ast, ast _ module_info.player + 3, ast _ module_info.fastplay);
		break;
	case ASAP_TYPE_TMC:
		if (--ast _ tmc_per_frame_counter <= 0) {
			ast _ tmc_per_frame_counter = ast _ tmc_per_frame;
			call_6502(ast, ast _ module_info.player + 3, ast _ module_info.fastplay);
		}
		else
			call_6502(ast, ast _ module_info.player + 6, ast _ module_info.fastplay);
		break;
#endif
	}
