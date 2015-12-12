static struct pnp_card_device_id snd_interwave_pnpids[] = {
#ifndef SNDRV_STB
	/* Gravis UltraSound Plug & Play */
	{ .id = "GRV0001", .devs = { { .id = "GRV0000" } } },
	/* STB SoundRage32 */
	{ .id = "STB011a", .devs = { { .id = "STB0010" } } },
	/* MED3210 */
	{ .id = "DXP3201", .devs = { { .id = "DXP0010" } } },
	/* Dynasonic Pro */
	/* This device also have CDC1117:DynaSonix Pro Audio Effects Processor */
	{ .id = "CDC1111", .devs = { { .id = "CDC1112" } } },
	/* Panasonic PCA761AW Audio Card */
	{ .id = "ADV55ff", .devs = { { .id = "ADV0010" } } },
	/* InterWave STB without TEA6330T */
	{ .id = "ADV550a", .devs = { { .id = "ADV0010" } } },
#else
	/* InterWave STB with TEA6330T */
	{ .id = "ADV550a", .devs = { { .id = "ADV0010" }, { .id = "ADV0015" } } },
#endif
	{ .id = "" }
};
