const KUHL_M_C kuhl_m_c_kerberos[] = {
	{kuhl_m_kerberos_ptt,		L"ptt",			L"Pass-the-ticket [NT 6]"},
	{kuhl_m_kerberos_list,		L"list",		L"List ticket(s)"},
	{kuhl_m_kerberos_tgt,		L"tgt",			L"Retrieve the current TGT"},
	{kuhl_m_kerberos_purge,		L"purge",		L"Purge ticket(s)"},
	{kuhl_m_kerberos_golden,	L"golden",		L"Willy Wonka factory"},
#ifdef KERBEROS_TOOLS
	{kuhl_m_kerberos_decode,	L"decrypt",		L"Decrypt encoded ticket"},
	{kuhl_m_kerberos_pac_info,	L"pacinfo",		L"Some infos on PAC file"},
#endif
};
