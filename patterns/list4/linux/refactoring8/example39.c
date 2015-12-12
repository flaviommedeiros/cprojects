static struct pnp_card_device_id snd_sb16_pnpids[] = {
#ifndef SNDRV_SBAWE
	/* Sound Blaster 16 PnP */
	{ .id = "CTL0024", .devs = { { "CTL0031" } } },
	/* Sound Blaster 16 PnP */
	{ .id = "CTL0025", .devs = { { "CTL0031" } } },
	/* Sound Blaster 16 PnP */
	{ .id = "CTL0026", .devs = { { "CTL0031" } } },
	/* Sound Blaster 16 PnP */
	{ .id = "CTL0027", .devs = { { "CTL0031" } } },
	/* Sound Blaster 16 PnP */
	{ .id = "CTL0028", .devs = { { "CTL0031" } } },
	/* Sound Blaster 16 PnP */
	{ .id = "CTL0029", .devs = { { "CTL0031" } } },
	/* Sound Blaster 16 PnP */
	{ .id = "CTL002a", .devs = { { "CTL0031" } } },
	/* Sound Blaster 16 PnP */
	/* Note: This card has also a CTL0051:StereoEnhance device!!! */
	{ .id = "CTL002b", .devs = { { "CTL0031" } } },
	/* Sound Blaster 16 PnP */
	{ .id = "CTL002c", .devs = { { "CTL0031" } } },
	/* Sound Blaster Vibra16S */
	{ .id = "CTL0051", .devs = { { "CTL0001" } } },
	/* Sound Blaster Vibra16C */
	{ .id = "CTL0070", .devs = { { "CTL0001" } } },
	/* Sound Blaster Vibra16CL - added by ctm@ardi.com */
	{ .id = "CTL0080", .devs = { { "CTL0041" } } },
	/* Sound Blaster 16 'value' PnP. It says model ct4130 on the pcb, */
	/* but ct4131 on a sticker on the board.. */
	{ .id = "CTL0086", .devs = { { "CTL0041" } } },
	/* Sound Blaster Vibra16X */
	{ .id = "CTL00f0", .devs = { { "CTL0043" } } },
	/* Sound Blaster 16 (Virtual PC 2004) */
	{ .id = "tBA03b0", .devs = { {.id="PNPb003" } } },
#else  /* SNDRV_SBAWE defined */
	/* Sound Blaster AWE 32 PnP */
	{ .id = "CTL0035", .devs = { { "CTL0031" }, { "CTL0021" } } },
	/* Sound Blaster AWE 32 PnP */
	{ .id = "CTL0039", .devs = { { "CTL0031" }, { "CTL0021" } } },
	/* Sound Blaster AWE 32 PnP */
	{ .id = "CTL0042", .devs = { { "CTL0031" }, { "CTL0021" } } },
	/* Sound Blaster AWE 32 PnP */
	{ .id = "CTL0043", .devs = { { "CTL0031" }, { "CTL0021" } } },
	/* Sound Blaster AWE 32 PnP */
	/* Note: This card has also a CTL0051:StereoEnhance device!!! */
	{ .id = "CTL0044", .devs = { { "CTL0031" }, { "CTL0021" } } },
	/* Sound Blaster AWE 32 PnP */
	/* Note: This card has also a CTL0051:StereoEnhance device!!! */
	{ .id = "CTL0045", .devs = { { "CTL0031" }, { "CTL0021" } } },
	/* Sound Blaster AWE 32 PnP */
	{ .id = "CTL0046", .devs = { { "CTL0031" }, { "CTL0021" } } },
	/* Sound Blaster AWE 32 PnP */
	{ .id = "CTL0047", .devs = { { "CTL0031" }, { "CTL0021" } } },
	/* Sound Blaster AWE 32 PnP */
	{ .id = "CTL0048", .devs = { { "CTL0031" }, { "CTL0021" } } },
	/* Sound Blaster AWE 32 PnP */
	{ .id = "CTL0054", .devs = { { "CTL0031" }, { "CTL0021" } } },
	/* Sound Blaster AWE 32 PnP */
	{ .id = "CTL009a", .devs = { { "CTL0041" }, { "CTL0021" } } },
	/* Sound Blaster AWE 32 PnP */
	{ .id = "CTL009c", .devs = { { "CTL0041" }, { "CTL0021" } } },
	/* Sound Blaster 32 PnP */
	{ .id = "CTL009f", .devs = { { "CTL0041" }, { "CTL0021" } } },
	/* Sound Blaster AWE 64 PnP */
	{ .id = "CTL009d", .devs = { { "CTL0042" }, { "CTL0022" } } },
	/* Sound Blaster AWE 64 PnP Gold */
	{ .id = "CTL009e", .devs = { { "CTL0044" }, { "CTL0023" } } },
	/* Sound Blaster AWE 64 PnP Gold */
	{ .id = "CTL00b2", .devs = { { "CTL0044" }, { "CTL0023" } } },
	/* Sound Blaster AWE 64 PnP */
	{ .id = "CTL00c1", .devs = { { "CTL0042" }, { "CTL0022" } } },
	/* Sound Blaster AWE 64 PnP */
	{ .id = "CTL00c3", .devs = { { "CTL0045" }, { "CTL0022" } } },
	/* Sound Blaster AWE 64 PnP */
	{ .id = "CTL00c5", .devs = { { "CTL0045" }, { "CTL0022" } } },
	/* Sound Blaster AWE 64 PnP */
	{ .id = "CTL00c7", .devs = { { "CTL0045" }, { "CTL0022" } } },
	/* Sound Blaster AWE 64 PnP */
	{ .id = "CTL00e4", .devs = { { "CTL0045" }, { "CTL0022" } } },
	/* Sound Blaster AWE 64 PnP */
	{ .id = "CTL00e9", .devs = { { "CTL0045" }, { "CTL0022" } } },
	/* Sound Blaster 16 PnP (AWE) */
	{ .id = "CTL00ed", .devs = { { "CTL0041" }, { "CTL0070" } } },
	/* Generic entries */
	{ .id = "CTLXXXX" , .devs = { { "CTL0031" }, { "CTL0021" } } },
	{ .id = "CTLXXXX" , .devs = { { "CTL0041" }, { "CTL0021" } } },
	{ .id = "CTLXXXX" , .devs = { { "CTL0042" }, { "CTL0022" } } },
	{ .id = "CTLXXXX" , .devs = { { "CTL0044" }, { "CTL0023" } } },
	{ .id = "CTLXXXX" , .devs = { { "CTL0045" }, { "CTL0022" } } },
#endif /* SNDRV_SBAWE */
	{ .id = "", }
};
