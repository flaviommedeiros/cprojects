#ifdef CFG_ROMBOOT
if (board_bootdev_rom(sih)) {
			rom_envram_size = ROM_ENVRAM_SPACE;
		}
		else
#endif
		{
			rom_envram_size = 0;
		}
