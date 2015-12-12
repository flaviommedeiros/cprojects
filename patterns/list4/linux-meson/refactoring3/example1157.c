switch (fault_num) {
#ifndef __tilepro__
	case INT_IDN_FIREWALL:
		hwt = &hardwall_types[HARDWALL_IDN];
		break;
#endif
	case INT_UDN_FIREWALL:
		hwt = &hardwall_types[HARDWALL_UDN];
		break;
	default:
		BUG();
	}
