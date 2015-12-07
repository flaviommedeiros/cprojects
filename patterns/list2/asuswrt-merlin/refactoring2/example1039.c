#ifdef LP_MULTIBYTE_AVAILABLE
if (!MultiByteToWideChar
                (CP_ACP, 0, extdir, len_0, (WCHAR *)wdir, len_0))
#endif
                for (index = 0; index < len_0; index++)
                    wdir[index] = (TCHAR)extdir[index];
