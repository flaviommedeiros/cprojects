static s_p_options_t bg_conf_file_options[] = {
#ifndef HAVE_BG_L_P
	{"AllowSubBlockAllocations", S_P_BOOLEAN},
#elif defined HAVE_BGL
	{"BlrtsImage", S_P_STRING},
	{"LinuxImage", S_P_STRING},
	{"RamDiskImage", S_P_STRING},
	{"AltBlrtsImage", S_P_ARRAY, parse_image, NULL},
	{"AltLinuxImage", S_P_ARRAY, parse_image, NULL},
	{"AltRamDiskImage", S_P_ARRAY, parse_image, NULL},
#elif defined HAVE_BGP
	{"CnloadImage", S_P_STRING},
	{"IoloadImage", S_P_STRING},
	{"AltCnloadImage", S_P_ARRAY, parse_image, NULL},
	{"AltIoloadImage", S_P_ARRAY, parse_image, NULL},
#endif
	{"DefaultConnType", S_P_STRING},
	{"DenyPassthrough", S_P_STRING},
	{"LayoutMode", S_P_STRING},
	{"MloaderImage", S_P_STRING},
	{"BridgeAPILogFile", S_P_STRING},
	{"BridgeAPIVerbose", S_P_UINT16},
	{"BasePartitionNodeCnt", S_P_UINT16},
	{"MidplaneNodeCnt", S_P_UINT16},
	{"NodeCardNodeCnt", S_P_UINT16},
	{"NodeBoardNodeCnt", S_P_UINT16},
	{"Numpsets", S_P_UINT16},
	{"IONodesPerMP", S_P_UINT16},
	{"MaxBlockInError", S_P_UINT16},
	{"BPs", S_P_ARRAY, parse_blockreq, destroy_select_ba_request},
	{"MPs", S_P_ARRAY, parse_blockreq, destroy_select_ba_request},
	/* these are just going to be put into a list that will be
	   freed later don't free them after reading them */
	{"AltMloaderImage", S_P_ARRAY, parse_image, NULL},
	{"SubMidplaneSystem", S_P_BOOLEAN},
	{"RebootQOSList", S_P_STRING},
	{NULL}
};
