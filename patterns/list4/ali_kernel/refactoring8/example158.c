static struct parisc_device_id gscps2_device_tbl[] = {
	{ HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00084 }, /* LASI PS/2 */
#ifdef DINO_TESTED
	{ HPHW_FIO, HVERSION_REV_ANY_ID, HVERSION_ANY_ID, 0x00096 }, /* DINO PS/2 */
#endif
	{ 0, }	/* 0 terminated list */
};
