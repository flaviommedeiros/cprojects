if(
		GetVersionEx((LPOSVERSIONINFO) &osVersionInfos)
		#ifdef _M_IX86
		&& IsWow64Process(GetCurrentProcess(), &isWow64)
		#endif
		)
	{
		kprintf(
			L"\n" MIMIKATZ L" " MIMIKATZ_VERSION L" (arch " MIMIKATZ_ARCH L")\n"
			L"API    -  Windows NT %u.%u build %u service pack %hu.%hu (arch x%s)\n"
			L"NT     -  Windows NT %u.%u build %u\n",
			osVersionInfos.dwMajorVersion, osVersionInfos.dwMinorVersion,
			osVersionInfos.dwBuildNumber, osVersionInfos.wServicePackMajor, osVersionInfos.wServicePackMinor, isWow64 ? L"64" : L"86",
			MIMIKATZ_NT_MAJOR_VERSION, MIMIKATZ_NT_MINOR_VERSION, MIMIKATZ_NT_BUILD_NUMBER
			);
	}
