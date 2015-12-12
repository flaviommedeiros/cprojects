if (SOCINFO_VERSION_MAJOR(soc_platform_version) < 3) {
			spi_register_board_info(lcdc_samsung_spi_board_info,
				ARRAY_SIZE(lcdc_samsung_spi_board_info));
		} else
#endif
		{
#ifdef CONFIG_FB_MSM_LCDC_AUO_WVGA
			spi_register_board_info(lcdc_auo_spi_board_info,
				ARRAY_SIZE(lcdc_auo_spi_board_info));
#endif
		}
#endif
