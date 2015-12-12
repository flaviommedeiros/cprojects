static struct hpsb_config_rom_entry *const config_rom_entries[] = {
#ifdef CONFIG_IEEE1394_ETH1394_ROM_ENTRY
	&ip1394_entry,
#endif
};
