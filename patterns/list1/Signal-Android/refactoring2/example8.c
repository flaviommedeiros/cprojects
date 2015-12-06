#ifndef OPENSSL_NO_MULTIBYTE
if (!MultiByteToWideChar(CP_ACP,0,fmta,len_0,fmtw,len_0))
#endif
	    for (i=0;i<len_0;i++) fmtw[i]=(WCHAR)fmta[i];
