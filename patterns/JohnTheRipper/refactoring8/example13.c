static struct fmt_tests tests[] = {
	{"DDIC$6066CD3147915331EC4C602847D27A75EB3E8F0A", "DDIC"},
	// invalid, because password is too short (would work during login, but not during password change),
	// magnum wants to keep thesse tests anyway, because they help verifying key buffer cleaning:
	{"F           $646A0AD270DF651065669A45D171EDD62DFE39A1", "X"},
	{"JOHNNY                                  $7D79B478E70CAAE63C41E0824EAB644B9070D10A", "CYBERPUNK"},
	{"VAN$D15597367F24090F0A501962788E9F19B3604E73", "hauser"},
	{"ROOT$1194E38F14B9F3F8DA1B181F14DEB70E7BDCC239", "KID"},
	// invalid, because password is too short (would work during login, but not during password change):
	{"MAN$22886450D0AB90FDA7F91C4F3DD5619175B372EA", "u"},
#if 0
	// This test case is invalid since the user name can just be
	// up to 12 characters long.
	// So, unless the user name doesn't contain non-ascii characters,
	// it will not be longer than 12 bytes.
	// Also, "-------" is not a valid SAP password, since the first 3 characters
	// are identical.
	{"------------------------------------$463BDDCF2D2D6E07FC64C075A0802BD87A39BBA6", "-------"},
#else
	// SAP user name consisting of 12 consecutive EURO characters:
	{"\xe2\x82\xac\xe2\x82\xac\xe2\x82\xac\xe2\x82\xac\xe2\x82\xac\xe2\x82\xac"
	 "\xe2\x82\xac\xe2\x82\xac\xe2\x82\xac\xe2\x82\xac\xe2\x82\xac\xe2\x82\xac"
	 "$B20D15C088481780CD44FCF2003AAAFBD9710C7C", "--+----"},
#endif
	{"SAP*                                $60A0F7E06D95BC9FB45F605BDF1F7B660E5D5D4E", "MaStEr"},
	{"DOLLAR$$$---$E0180FD4542D8B6715E7D0D9EDE7E2D2E40C3D4D", "Dollar$$$---"},
	{NULL}
};
