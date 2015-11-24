static int bin_pe_init_hdr(struct PE_(r_bin_pe_obj_t)* bin) {
	if (!(bin->dos_header = malloc(sizeof(PE_(image_dos_header))))) {
		r_sys_perror ("malloc (dos header)");
		return false;
	}
	if (r_buf_read_at (bin->b, 0, (ut8*)bin->dos_header, sizeof(PE_(image_dos_header))) == -1) {
		eprintf("Warning: read (dos header)\n");
		return false;
	}
	sdb_num_set (bin->kv, "pe_dos_header.offset", 0, 0);
	sdb_set (bin->kv, "pe_dos_header.format", "[2]zwwwwwwwwwwwww[4]www[10]wx"
			" e_magic e_cblp e_cp e_crlc e_cparhdr e_minalloc e_maxalloc"
			" e_ss e_sp e_csum e_ip e_cs e_lfarlc e_ovno e_res e_oemid"
			" e_oeminfo e_res2 e_lfanew", 0);
	if (bin->dos_header->e_lfanew > (unsigned int)bin->size) {
		eprintf("Invalid e_lfanew field\n");
		return false;
	}
	if (!(bin->nt_headers = malloc (sizeof (PE_(image_nt_headers))))) {
		r_sys_perror("malloc (nt header)");
		return false;
	}
	bin->nt_header_offset = bin->dos_header->e_lfanew;
	if (r_buf_read_at (bin->b, bin->dos_header->e_lfanew,
			(ut8*)bin->nt_headers, sizeof (PE_(image_nt_headers))) == -1) {
		eprintf ("Warning: read (dos header)\n");
		return false;
	}
	sdb_set (bin->kv, "pe_magic.cparse", "enum pe_magic { IMAGE_NT_OPTIONAL_HDR32_MAGIC=0x10b, IMAGE_NT_OPTIONAL_HDR64_MAGIC=0x20b, IMAGE_ROM_OPTIONAL_HDR_MAGIC=0x107 };", 0);
	sdb_set (bin->kv, "pe_subsystem.cparse", "enum pe_subsystem { IMAGE_SUBSYSTEM_UNKNOWN=0, IMAGE_SUBSYSTEM_NATIVE=1, IMAGE_SUBSYSTEM_WINDOWS_GUI=2, "
					  " IMAGE_SUBSYSTEM_WINDOWS_CUI=3, IMAGE_SUBSYSTEM_OS2_CUI=5, IMAGE_SUBSYSTEM_POSIX_CUI=7, IMAGE_SUBSYSTEM_WINDOWS_CE_GUI=9, "
					  " IMAGE_SUBSYSTEM_EFI_APPLICATION=10, IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER=11, IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER=12, "
					  " IMAGE_SUBSYSTEM_EFI_ROM=13, IMAGE_SUBSYSTEM_XBOX=14, IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION=16 };", 0);
	sdb_set (bin->kv, "pe_dllcharacteristics.cparse", "enum pe_dllcharacteristics { IMAGE_LIBRARY_PROCESS_INIT=0x0001, IMAGE_LIBRARY_PROCESS_TERM=0x0002, "
					  " IMAGE_LIBRARY_THREAD_INIT=0x0004, IMAGE_LIBRARY_THREAD_TERM=0x0008, IMAGE_DLLCHARACTERISTICS_HIGH_ENTROPY_VA=0x0020, "
					  " IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE=0x0040, IMAGE_DLLCHARACTERISTICS_FORCE_INTEGRITY=0x0080, "
					  " IMAGE_DLLCHARACTERISTICS_NX_COMPAT=0x0100, IMAGE_DLLCHARACTERISTICS_NO_ISOLATION=0x0200,IMAGE_DLLCHARACTERISTICS_NO_SEH=0x0400, "
					  " IMAGE_DLLCHARACTERISTICS_NO_BIND=0x0800, IMAGE_DLLCHARACTERISTICS_APPCONTAINER=0x1000, IMAGE_DLLCHARACTERISTICS_WDM_DRIVER=0x2000, "
					  " IMAGE_DLLCHARACTERISTICS_GUARD_CF=0x4000, IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE=0x8000};", 0);
	#if R_BIN_PE64
	sdb_num_set (bin->kv, "pe_nt_image_headers64.offset", bin->dos_header->e_lfanew, 0);
	sdb_set (bin->kv, "pe_nt_image_headers64.format", "[4]z?? signature (pe_image_file_header)fileHeader (pe_image_optional_header64)optionalHeader", 0);
	sdb_set (bin->kv, "pe_image_optional_header64.format", "[2]Ebbxxxxxqxxwwwwwwxxxx[2]E[2]Bqqqqxx[16]?"
					  " (pe_magic)magic majorLinkerVersion minorLinkerVersion sizeOfCode sizeOfInitializedData"
					  " sizeOfUninitializedData addressOfEntryPoint baseOfCode imageBase"
					  " sectionAlignment fileAlignment majorOperatingSystemVersion minorOperatingSystemVersion"
					  " majorImageVersion minorImageVersion majorSubsystemVersion minorSubsystemVersion"
					  " win32VersionValue sizeOfImage sizeOfHeaders checkSum (pe_subsystem)subsystem (pe_dllcharacteristics)dllCharacteristics"
					  " sizeOfStackReserve sizeOfStackCommit sizeOfHeapReserve sizeOfHeapCommit loaderFlags"
					  " numberOfRvaAndSizes (pe_image_data_directory)dataDirectory", 0);
	#else
	sdb_num_set (bin->kv, "pe_nt_image_headers32.offset", bin->dos_header->e_lfanew, 0);
	sdb_set (bin->kv, "pe_nt_image_headers32.format", "[4]z?? signature (pe_image_file_header)fileHeader (pe_image_optional_header32)optionalHeader", 0);
	sdb_set (bin->kv, "pe_image_optional_header32.format", "[2]Ebbxxxxxxxxxwwwwwwxxxx[2]E[2]Bxxxxxx[16]?"
					  " (pe_magic)magic majorLinkerVersion minorLinkerVersion sizeOfCode sizeOfInitializedData"
					  " sizeOfUninitializedData addressOfEntryPoint baseOfCode baseOfData imageBase"
					  " sectionAlignment fileAlignment majorOperatingSystemVersion minorOperatingSystemVersion"
					  " majorImageVersion minorImageVersion majorSubsystemVersion minorSubsystemVersion"
					  " win32VersionValue sizeOfImage sizeOfHeaders checkSum (pe_subsystem)subsystem (pe_dllcharacteristics)dllCharacteristics"
					  " sizeOfStackReserve sizeOfStackCommit sizeOfHeapReserve sizeOfHeapCommit loaderFlags numberOfRvaAndSizes"
					  " (pe_image_data_directory)dataDirectory", 0);
	#endif
	sdb_set (bin->kv, "pe_machine.cparse", "enum pe_machine { IMAGE_FILE_MACHINE_I386=0x014c, IMAGE_FILE_MACHINE_IA64=0x0200, IMAGE_FILE_MACHINE_AMD64=0x8664 };", 0);
	sdb_set (bin->kv, "pe_characteristics.cparse", "enum pe_characteristics { "
					  " IMAGE_FILE_RELOCS_STRIPPED=0x0001, IMAGE_FILE_EXECUTABLE_IMAGE=0x0002, IMAGE_FILE_LINE_NUMS_STRIPPED=0x0004, "
					  " IMAGE_FILE_LOCAL_SYMS_STRIPPED=0x0008, IMAGE_FILE_AGGRESIVE_WS_TRIM=0x0010, IMAGE_FILE_LARGE_ADDRESS_AWARE=0x0020, "
					  " IMAGE_FILE_BYTES_REVERSED_LO=0x0080, IMAGE_FILE_32BIT_MACHINE=0x0100, IMAGE_FILE_DEBUG_STRIPPED=0x0200, "
					  " IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP=0x0400, IMAGE_FILE_NET_RUN_FROM_SWAP=0x0800, IMAGE_FILE_SYSTEM=0x1000, "
					  " IMAGE_FILE_DLL=0x2000, IMAGE_FILE_UP_SYSTEM_ONLY=0x4000, IMAGE_FILE_BYTES_REVERSED_HI=0x8000 };", 0);
	sdb_set (bin->kv, "pe_image_file_header.format", "[2]Ewtxxw[2]B"
					  " (pe_machine)machine numberOfSections timeDateStamp pointerToSymbolTable"
					  " numberOfSymbols sizeOfOptionalHeader (pe_characteristics)characteristics", 0);
	sdb_set (bin->kv, "pe_image_data_directory.format", "xx virtualAddress size",0);

	// adding compile time to the SDB
	 {
		struct my_timezone {
			int tz_minuteswest;     /* minutes west of Greenwich */
			int tz_dsttime;         /* type of DST correction */
		} tz;
		struct timeval tv;
		int gmtoff;
		char *timestr;
		time_t ts = (time_t)bin->nt_headers->file_header.TimeDateStamp;
		sdb_num_set (bin->kv, "image_file_header.TimeDateStamp",
			bin->nt_headers->file_header.TimeDateStamp, 0);
		gettimeofday (&tv, (void*)&tz);
		gmtoff = (int)(tz.tz_minuteswest*60); // in seconds
		ts += gmtoff;
		timestr = r_str_chop (strdup (ctime (&ts)));
		// gmt offset for pe date is t->tm_gmtoff
		sdb_set_owned (bin->kv,
			"image_file_header.TimeDateStamp_string",
			      timestr, 0);
	 }

	if (strncmp ((char*)&bin->dos_header->e_magic, "MZ", 2) ||
		strncmp ((char*)&bin->nt_headers->Signature, "PE", 2))
			return false;
	return true;
}
