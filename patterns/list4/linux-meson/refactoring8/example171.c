struct tulip_chip_table tulip_tbl[] = {
  { }, /* placeholder for array, slot unused currently */
  { }, /* placeholder for array, slot unused currently */

  /* DC21140 */
  { "Digital DS21140 Tulip", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABLE | CSR12_IN_SROM | HAS_PCI_MWI, tulip_timer,
	tulip_media_task },

  /* DC21142, DC21143 */
  { "Digital DS21142/43 Tulip", 128, 0x0801fbff,
	HAS_MII | HAS_MEDIA_TABLE | ALWAYS_CHECK_MII | HAS_ACPI | HAS_NWAY
	| HAS_INTR_MITIGATION | HAS_PCI_MWI, tulip_timer, t21142_media_task },

  /* LC82C168 */
  { "Lite-On 82c168 PNIC", 256, 0x0001fbef,
	HAS_MII | HAS_PNICNWAY, pnic_timer, },

  /* MX98713 */
  { "Macronix 98713 PMAC", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABLE | CSR12_IN_SROM, mxic_timer, },

  /* MX98715 */
  { "Macronix 98715 PMAC", 256, 0x0001ebef,
	HAS_MEDIA_TABLE, mxic_timer, },

  /* MX98725 */
  { "Macronix 98725 PMAC", 256, 0x0001ebef,
	HAS_MEDIA_TABLE, mxic_timer, },

  /* AX88140 */
  { "ASIX AX88140", 128, 0x0001fbff,
	HAS_MII | HAS_MEDIA_TABLE | CSR12_IN_SROM | MC_HASH_ONLY
	| IS_ASIX, tulip_timer, tulip_media_task },

  /* PNIC2 */
  { "Lite-On PNIC-II", 256, 0x0801fbff,
	HAS_MII | HAS_NWAY | HAS_8023X | HAS_PCI_MWI, pnic2_timer, },

  /* COMET */
  { "ADMtek Comet", 256, 0x0001abef,
	HAS_MII | MC_HASH_ONLY | COMET_MAC_ADDR, comet_timer, },

  /* COMPEX9881 */
  { "Compex 9881 PMAC", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABLE | CSR12_IN_SROM, mxic_timer, },

  /* I21145 */
  { "Intel DS21145 Tulip", 128, 0x0801fbff,
	HAS_MII | HAS_MEDIA_TABLE | ALWAYS_CHECK_MII | HAS_ACPI
	| HAS_NWAY | HAS_PCI_MWI, tulip_timer, tulip_media_task },

  /* DM910X */
#ifdef CONFIG_TULIP_DM910X
  { "Davicom DM9102/DM9102A", 128, 0x0001ebef,
	HAS_MII | HAS_MEDIA_TABLE | CSR12_IN_SROM | HAS_ACPI,
	tulip_timer, tulip_media_task },
#else
  { NULL },
#endif

  /* RS7112 */
  { "Conexant LANfinity", 256, 0x0001ebef,
	HAS_MII | HAS_ACPI, tulip_timer, tulip_media_task },

};
