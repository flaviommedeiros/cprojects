#ifdef CONFIG_BCM47XX_BCMA
if  (bcm47xx_bus_type ==  BCM47XX_BUS_TYPE_BCMA)
		return bcm47xx_pcibios_plat_dev_init_bcma(dev);
	else
#endif
		return 0;
