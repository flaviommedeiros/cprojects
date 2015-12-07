switch (get_packed_ext(filename)) {
	case ASAP_EXT('S', 'A', 'P'):
		return parse_sap(ast, module_info, module, module_len);
#ifndef ASAP_ONLY_SAP
	case ASAP_EXT('C', 'M', 'C'):
		return parse_cmc(ast, module_info, module, module_len, ASAP_TYPE_CMC);
	case ASAP_EXT('C', 'M', '3'):
		return parse_cm3(ast, module_info, module, module_len);
	case ASAP_EXT('C', 'M', 'R'):
		return parse_cmc(ast, module_info, module, module_len, ASAP_TYPE_CMR);
	case ASAP_EXT('C', 'M', 'S'):
		return parse_cms(ast, module_info, module, module_len);
	case ASAP_EXT('D', 'M', 'C'):
		module_info _ fastplay = 156;
		return parse_cmc(ast, module_info, module, module_len, ASAP_TYPE_CMC);
	case ASAP_EXT('D', 'L', 'T'):
		return parse_dlt(ast, module_info, module, module_len);
	case ASAP_EXT('M', 'P', 'T'):
		return parse_mpt(ast, module_info, module, module_len);
	case ASAP_EXT('M', 'P', 'D'):
		module_info _ fastplay = 156;
		return parse_mpt(ast, module_info, module, module_len);
	case ASAP_EXT('R', 'M', 'T'):
		return parse_rmt(ast, module_info, module, module_len);
	case ASAP_EXT('T', 'M', 'C'):
	case ASAP_EXT('T', 'M', '8'):
		return parse_tmc(ast, module_info, module, module_len);
	case ASAP_EXT('T', 'M', '2'):
		return parse_tm2(ast, module_info, module, module_len);
#endif
	default:
		return FALSE;
	}
