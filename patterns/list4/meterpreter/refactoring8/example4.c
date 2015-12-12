const KUHL_M_SEKURLSA_LOCAL_HELPER lsassLocalHelpers[] = {
	{kuhl_m_sekurlsa_nt5_init,	kuhl_m_sekurlsa_nt5_clean,	kuhl_m_sekurlsa_nt5_acquireKeys,	&kuhl_m_sekurlsa_nt5_pLsaProtectMemory,	&kuhl_m_sekurlsa_nt5_pLsaUnprotectMemory},
	{kuhl_m_sekurlsa_nt6_init,	kuhl_m_sekurlsa_nt6_clean,	kuhl_m_sekurlsa_nt6_acquireKeys,	&kuhl_m_sekurlsa_nt6_pLsaProtectMemory,	&kuhl_m_sekurlsa_nt6_pLsaUnprotectMemory},
#ifdef LSASS_DECRYPT
	{kuhl_m_sekurlsa_nt63_init,	kuhl_m_sekurlsa_nt63_clean,	kuhl_m_sekurlsa_nt63_acquireKeys,	&kuhl_m_sekurlsa_nt63_pLsaProtectMemory,&kuhl_m_sekurlsa_nt63_pLsaUnprotectMemory},
#endif
};
