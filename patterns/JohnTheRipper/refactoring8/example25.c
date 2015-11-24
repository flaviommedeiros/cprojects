static struct fmt_tests _Preloads_16[] =
{
	// NOTE the $ is the byte starting the salt block, and the $$2 is the
	// pattern showing where to 'split off' the
	{"$dynamic_16$5ce496c635f96ac1ccd87518d4274b49$aaaSXB$$2salt2","test1"},
	{"$dynamic_16$2f49a8804a3aee4da3c219539fc93c6d$123456$$2ssss2","thatsworking"},
	{"$dynamic_16$d8deb4f271694c7a9a6c54f5068e3825$5555hh$$2sxxx3","test3"},
	// repeat the hash in exactly the same format as it gets stored in john.pot
	{"$dynamic_16$d8deb4f271694c7a9a6c54f5068e3825$HEX$3535353568682424327378787833","test3"},
	{"$dynamic_16$0b714c79c5790c913a6e44faad39f597$12345678901234567890123$$23IJIps", "1234567890123456789012345678901234567890123456789012345"},
#ifndef SIMD_COEF_32
	{"$dynamic_16$1e27f26c540f2980809f4d74989e20e3$12345678901234567890123$$2730ZnC", "12345678901234567890123456789012345678901234567890123456789012345678901234567890"},
#endif
	{NULL}
};
