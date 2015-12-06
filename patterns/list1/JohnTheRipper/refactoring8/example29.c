static struct fmt_tests _Preloads_29[] =
{
	{"$dynamic_29$16c47151c18ac087cd12b3a70746c790","test1"},
	// these U= test strings will ONLY be loaded in --encoding=utf8 mode
	{"U=$dynamic_29$94a4e171de16580742c4d141e6607bf7","\xE2\x82\xAC"},
	{"U=$dynamic_29$03c60810f0e54d16e826aca385d776c8","\xE2\x82\xAC\xE2\x82\xAC"},
	{"U=$dynamic_29$2d554433d7cde7ec8d16aaf126c3be6b","\xE2\x82\xAC\xC3\xBC"},
	{"U=$dynamic_29$8007d9070b27db7b30433df2cd10abc1","\xC3\xBC\xE2\x82\xAC"},
	// these A= test strings will ONLY be loaded if we are NOT in --encoding=utf8 mode
	{"A=$dynamic_29$ea7ab2b5c07650badab30790d0c9b63e","\xFC"},
	{"A=$dynamic_29$f0a0b9f1dea0e458cec9a284ff434d44","\xFC\xFC"},
	{"A=$dynamic_29$d25a0b436b768777cc9a343d283dbf5a","\xFC\xFC\xFC"},
	{"A=$dynamic_29$719917322bf12168f8c55939e4fec8de","\xFC\xFC\xFC\xFC"},
	{"$dynamic_29$d41d8cd98f00b204e9800998ecf8427e",""},
	{"$dynamic_29$9c3abef89ff76f8acd80eae37b35f64f","test2"},
	{"$dynamic_29$849ee1b88b5d887bdb058180a666b450","test3"},
	{"$dynamic_29$8c4cb7e8b33b56a833cdaa8673f3b425","test4"},
	{"$dynamic_29$537e738b1ac5551f65106368dc301ece","thatsworking"},
	{"$dynamic_29$35a4af9e0a634cd450551137193da28f", "123456789012345678901234567"},
#ifndef SIMD_COEF_32
	{"$dynamic_29$002ca7054ae8657c55fb8b32008e113d", "1234567890123456789012345678901234567890"},
#endif
	{NULL}
};
