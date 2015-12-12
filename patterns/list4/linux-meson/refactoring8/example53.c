static struct ac97_quirk ac97_quirks[] = {
        {
		.subvendor = 0x0e11,
		.subdevice = 0x000e,
		.name = "Compaq Deskpro EN",	/* AD1885 */
		.type = AC97_TUNE_HP_ONLY
        },
	{
		.subvendor = 0x0e11,
		.subdevice = 0x008a,
		.name = "Compaq Evo W4000",	/* AD1885 */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x0e11,
		.subdevice = 0x00b8,
		.name = "Compaq Evo D510C",
		.type = AC97_TUNE_HP_ONLY
	},
        {
		.subvendor = 0x0e11,
		.subdevice = 0x0860,
		.name = "HP/Compaq nx7010",
		.type = AC97_TUNE_MUTE_LED
        },
	{
		.subvendor = 0x1014,
		.subdevice = 0x0534,
		.name = "ThinkPad X31",
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendor = 0x1014,
		.subdevice = 0x1f00,
		.name = "MS-9128",
		.type = AC97_TUNE_ALC_JACK
	},
	{
		.subvendor = 0x1014,
		.subdevice = 0x0267,
		.name = "IBM NetVista A30p",	/* AD1981B */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1025,
		.subdevice = 0x0082,
		.name = "Acer Travelmate 2310",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1025,
		.subdevice = 0x0083,
		.name = "Acer Aspire 3003LCi",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x00d8,
		.name = "Dell Precision 530",	/* AD1885 */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x010d,
		.name = "Dell",	/* which model?  AD1885 */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x0126,
		.name = "Dell Optiplex GX260",	/* AD1981A */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x012c,
		.name = "Dell Precision 650",	/* AD1981A */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x012d,
		.name = "Dell Precision 450",	/* AD1981B*/
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x0147,
		.name = "Dell",	/* which model?  AD1981B*/
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x0151,
		.name = "Dell Optiplex GX270",  /* AD1981B */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x014e,
		.name = "Dell D800", /* STAC9750/51 */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x0163,
		.name = "Dell Unknown",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x016a,
		.name = "Dell Inspiron 8600",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x0182,
		.name = "Dell Latitude D610",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x0186,
		.name = "Dell Latitude D810", /* cf. Malone #41015 */
		.type = AC97_TUNE_HP_MUTE_LED
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x0188,
		.name = "Dell Inspiron 6000",
		.type = AC97_TUNE_HP_MUTE_LED /* cf. Malone #41015 */
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x0189,
		.name = "Dell Inspiron 9300",
		.type = AC97_TUNE_HP_MUTE_LED
	},
	{
		.subvendor = 0x1028,
		.subdevice = 0x0191,
		.name = "Dell Inspiron 8600",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x103c,
		.subdevice = 0x006d,
		.name = "HP zv5000",
		.type = AC97_TUNE_MUTE_LED	/*AD1981B*/
	},
	{	/* FIXME: which codec? */
		.subvendor = 0x103c,
		.subdevice = 0x00c3,
		.name = "HP xw6000",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x103c,
		.subdevice = 0x088c,
		.name = "HP nc8000",
		.type = AC97_TUNE_HP_MUTE_LED
	},
	{
		.subvendor = 0x103c,
		.subdevice = 0x0890,
		.name = "HP nc6000",
		.type = AC97_TUNE_MUTE_LED
	},
	{
		.subvendor = 0x103c,
		.subdevice = 0x129d,
		.name = "HP xw8000",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x103c,
		.subdevice = 0x0938,
		.name = "HP nc4200",
		.type = AC97_TUNE_HP_MUTE_LED
	},
	{
		.subvendor = 0x103c,
		.subdevice = 0x099c,
		.name = "HP nx6110/nc6120",
		.type = AC97_TUNE_HP_MUTE_LED
	},
	{
		.subvendor = 0x103c,
		.subdevice = 0x0944,
		.name = "HP nc6220",
		.type = AC97_TUNE_HP_MUTE_LED
	},
	{
		.subvendor = 0x103c,
		.subdevice = 0x0934,
		.name = "HP nc8220",
		.type = AC97_TUNE_HP_MUTE_LED
	},
	{
		.subvendor = 0x103c,
		.subdevice = 0x12f1,
		.name = "HP xw8200",	/* AD1981B*/
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x103c,
		.subdevice = 0x12f2,
		.name = "HP xw6200",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x103c,
		.subdevice = 0x3008,
		.name = "HP xw4200",	/* AD1981B*/
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x104d,
		.subdevice = 0x8144,
		.name = "Sony",
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendor = 0x104d,
		.subdevice = 0x8197,
		.name = "Sony S1XP",
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendor = 0x104d,
		.subdevice = 0x81c0,
		.name = "Sony VAIO VGN-T350P", /*AD1981B*/
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendor = 0x104d,
		.subdevice = 0x81c5,
		.name = "Sony VAIO VGN-B1VP", /*AD1981B*/
		.type = AC97_TUNE_INV_EAPD
	},
 	{
		.subvendor = 0x1043,
		.subdevice = 0x80f3,
		.name = "ASUS ICH5/AD1985",
		.type = AC97_TUNE_AD_SHARING
	},
	{
		.subvendor = 0x10cf,
		.subdevice = 0x11c3,
		.name = "Fujitsu-Siemens E4010",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x10cf,
		.subdevice = 0x1225,
		.name = "Fujitsu-Siemens T3010",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x10cf,
		.subdevice = 0x1253,
		.name = "Fujitsu S6210",	/* STAC9750/51 */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x10cf,
		.subdevice = 0x127d,
		.name = "Fujitsu Lifebook P7010",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x10cf,
		.subdevice = 0x127e,
		.name = "Fujitsu Lifebook C1211D",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x10cf,
		.subdevice = 0x12ec,
		.name = "Fujitsu-Siemens 4010",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x10cf,
		.subdevice = 0x12f2,
		.name = "Fujitsu-Siemens Celsius H320",
		.type = AC97_TUNE_SWAP_HP
	},
	{
		.subvendor = 0x10f1,
		.subdevice = 0x2665,
		.name = "Fujitsu-Siemens Celsius",	/* AD1981? */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x10f1,
		.subdevice = 0x2885,
		.name = "AMD64 Mobo",	/* ALC650 */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x10f1,
		.subdevice = 0x2895,
		.name = "Tyan Thunder K8WE",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x10f7,
		.subdevice = 0x834c,
		.name = "Panasonic CF-R4",
		.type = AC97_TUNE_HP_ONLY,
	},
	{
		.subvendor = 0x110a,
		.subdevice = 0x0056,
		.name = "Fujitsu-Siemens Scenic",	/* AD1981? */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x11d4,
		.subdevice = 0x5375,
		.name = "ADI AD1985 (discrete)",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x1462,
		.subdevice = 0x5470,
		.name = "MSI P4 ATX 645 Ultra",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x161f,
		.subdevice = 0x202f,
		.name = "Gateway M520",
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendor = 0x161f,
		.subdevice = 0x203a,
		.name = "Gateway 4525GZ",		/* AD1981B */
		.type = AC97_TUNE_INV_EAPD
	},
	{
		.subvendor = 0x1734,
		.subdevice = 0x0088,
		.name = "Fujitsu-Siemens D1522",	/* AD1981 */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x8086,
		.subdevice = 0x2000,
		.mask = 0xfff0,
		.name = "Intel ICH5/AD1985",
		.type = AC97_TUNE_AD_SHARING
	},
	{
		.subvendor = 0x8086,
		.subdevice = 0x4000,
		.mask = 0xfff0,
		.name = "Intel ICH5/AD1985",
		.type = AC97_TUNE_AD_SHARING
	},
	{
		.subvendor = 0x8086,
		.subdevice = 0x4856,
		.name = "Intel D845WN (82801BA)",
		.type = AC97_TUNE_SWAP_HP
	},
	{
		.subvendor = 0x8086,
		.subdevice = 0x4d44,
		.name = "Intel D850EMV2",	/* AD1885 */
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x8086,
		.subdevice = 0x4d56,
		.name = "Intel ICH/AD1885",
		.type = AC97_TUNE_HP_ONLY
	},
	{
		.subvendor = 0x8086,
		.subdevice = 0x6000,
		.mask = 0xfff0,
		.name = "Intel ICH5/AD1985",
		.type = AC97_TUNE_AD_SHARING
	},
	{
		.subvendor = 0x8086,
		.subdevice = 0xe000,
		.mask = 0xfff0,
		.name = "Intel ICH5/AD1985",
		.type = AC97_TUNE_AD_SHARING
	},
#if 0 /* FIXME: this seems wrong on most boards */
	{
		.subvendor = 0x8086,
		.subdevice = 0xa000,
		.mask = 0xfff0,
		.name = "Intel ICH5/AD1985",
		.type = AC97_TUNE_HP_ONLY
	},
#endif
	{ } /* terminator */
};
