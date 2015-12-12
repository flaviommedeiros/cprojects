static struct pnp_card_device_id snd_opti9xx_pnpids[] = {
#ifndef OPTi93X
	/* OPTi 82C924 */
	{ .id = "OPT0924",
	  .devs = { { "OPT0000" }, { "OPT0002" }, { "OPT0005" } },
	  .driver_data = 0x0924 },
	/* OPTi 82C925 */
	{ .id = "OPT0925",
	  .devs = { { "OPT9250" }, { "OPT0002" }, { "OPT0005" } },
	  .driver_data = 0x0925 },
#else
	/* OPTi 82C931/3 */
	{ .id = "OPT0931", .devs = { { "OPT9310" }, { "OPT0002" } },
	  .driver_data = 0x0931 },
#endif	/* OPTi93X */
	{ .id = "" }
};
