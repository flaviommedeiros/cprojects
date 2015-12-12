static struct omap_board_config_kernel osk_config[] __initdata = {
#ifdef	CONFIG_OMAP_OSK_MISTRAL
	{ OMAP_TAG_LCD,			&osk_lcd_config },
#endif
};
