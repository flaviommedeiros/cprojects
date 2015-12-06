#ifdef LP_MULTIBYTE_AVAILABLE
if (!WideCharToMultiByte(CP_ACP, 0, (WCHAR *)wdir, len_0, (*ctx)->entry_name,
			       sizeof((*ctx)->entry_name), NULL, 0))
#endif
	for (index = 0; index < len_0; index++)
	  (*ctx)->entry_name[index] = (char)wdir[index];
