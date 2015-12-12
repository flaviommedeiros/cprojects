static struct persistent_ram_descriptor pram_descs[] = {
#ifdef CONFIG_ANDROID_RAM_CONSOLE
	{
		.name = "ram_console",
		.size = RAM_CONSOLE_SIZE,
	},
#endif
};
