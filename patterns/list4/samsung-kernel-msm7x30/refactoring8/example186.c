static const struct pcmcia_device_id wl_adapter_ids[] = {
#if !((HCF_TYPE) & HCF_TYPE_HII5)
	PCMCIA_DEVICE_MANF_CARD(0x0156, 0x0003),
	PCMCIA_DEVICE_PROD_ID12("Agere Systems", "Wireless PC Card Model 0110",
				0x33103a9b, 0xe175b0dd),
#else
	PCMCIA_DEVICE_MANF_CARD(0x0156, 0x0004),
	PCMCIA_DEVICE_PROD_ID12("Linksys", "WCF54G_Wireless-G_CompactFlash_Card",
				0x0733cc81, 0x98a599e1),
#endif  /* (HCF_TYPE) & HCF_TYPE_HII5 */
	PCMCIA_DEVICE_NULL,
};
