UCHAR RdIdleTimeTable[MAX_RD_REGION][4] =
{
	{9, 250, 250, 250},		// CE
#ifdef DFS_FCC_BW40_FIX
	{1, 250, 250, 250},		// FCC
#else
	{4, 250, 250, 250},		// FCC
#endif
	{4, 250, 250, 250},		// JAP
	{15, 250, 250, 250},	// JAP_W53
	{4, 250, 250, 250}		// JAP_W56
};
