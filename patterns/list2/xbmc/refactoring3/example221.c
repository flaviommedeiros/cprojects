switch (ast _ module_info.type) {
	case ASAP_TYPE_SAP_B:
		call_6502_init(ast, ast _ module_info.init, song, 0, 0);
		break;
	case ASAP_TYPE_SAP_C:
#ifndef ASAP_ONLY_SAP
	case ASAP_TYPE_CMC:
	case ASAP_TYPE_CM3:
	case ASAP_TYPE_CMR:
	case ASAP_TYPE_CMS:
#endif
		call_6502_init(ast, ast _ module_info.player + 3, 0x70, ast _ module_info.music, ast _ module_info.music >> 8);
		call_6502_init(ast, ast _ module_info.player + 3, 0x00, song, 0);
		break;
	case ASAP_TYPE_SAP_D:
	case ASAP_TYPE_SAP_S:
		ast _ cpu_a = song;
		ast _ cpu_x = 0x00;
		ast _ cpu_y = 0x00;
		ast _ cpu_s = 0xff;
		ast _ cpu_pc = ast _ module_info.init;
		break;
#ifndef ASAP_ONLY_SAP
	case ASAP_TYPE_DLT:
		call_6502_init(ast, ast _ module_info.player + 0x100, 0x00, 0x00, ast _ module_info.song_pos[song]);
		break;
	case ASAP_TYPE_MPT:
		call_6502_init(ast, ast _ module_info.player, 0x00, ast _ module_info.music >> 8, ast _ module_info.music);
		call_6502_init(ast, ast _ module_info.player, 0x02, ast _ module_info.song_pos[song], 0);
		break;
	case ASAP_TYPE_RMT:
		call_6502_init(ast, ast _ module_info.player, ast _ module_info.song_pos[song], ast _ module_info.music, ast _ module_info.music >> 8);
		break;
	case ASAP_TYPE_TMC:
	case ASAP_TYPE_TM2:
		call_6502_init(ast, ast _ module_info.player, 0x70, ast _ module_info.music >> 8, ast _ module_info.music);
		call_6502_init(ast, ast _ module_info.player, 0x00, song, 0);
		ast _ tmc_per_frame_counter = 1;
		break;
#endif
	}
