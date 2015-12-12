return (machine_is_omap_innovator()
		|| machine_is_omap_osk()
		|| machine_is_omap_apollon()
#ifndef CONFIG_MACH_OMAP_H4_OTG
		|| machine_is_omap_h4()
#endif
		|| machine_is_sx1()
		);
