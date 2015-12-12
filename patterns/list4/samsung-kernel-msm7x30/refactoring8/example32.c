static const struct hda_verb cs_errata_init_verbs[] = {
	{0x01, AC_VERB_SET_POWER_STATE, 0x00}, /* AFG: D0 */
	{0x11, AC_VERB_SET_PROC_STATE, 0x01},  /* VPW: processing on */

	{0x11, AC_VERB_SET_COEF_INDEX, 0x0008},
	{0x11, AC_VERB_SET_PROC_COEF, 0x9999},
	{0x11, AC_VERB_SET_COEF_INDEX, 0x0017},
	{0x11, AC_VERB_SET_PROC_COEF, 0xa412},
	{0x11, AC_VERB_SET_COEF_INDEX, 0x0001},
	{0x11, AC_VERB_SET_PROC_COEF, 0x0009},

	{0x07, AC_VERB_SET_POWER_STATE, 0x00}, /* S/PDIF Rx: D0 */
	{0x08, AC_VERB_SET_POWER_STATE, 0x00}, /* S/PDIF Tx: D0 */

	{0x11, AC_VERB_SET_COEF_INDEX, 0x0017},
	{0x11, AC_VERB_SET_PROC_COEF, 0x2412},
	{0x11, AC_VERB_SET_COEF_INDEX, 0x0008},
	{0x11, AC_VERB_SET_PROC_COEF, 0x0000},
	{0x11, AC_VERB_SET_COEF_INDEX, 0x0001},
	{0x11, AC_VERB_SET_PROC_COEF, 0x0008},
	{0x11, AC_VERB_SET_PROC_STATE, 0x00},

#if 0 /* Don't to set to D3 as we are in power-up sequence */
	{0x07, AC_VERB_SET_POWER_STATE, 0x03}, /* S/PDIF Rx: D3 */
	{0x08, AC_VERB_SET_POWER_STATE, 0x03}, /* S/PDIF Tx: D3 */
	/*{0x01, AC_VERB_SET_POWER_STATE, 0x03},*/ /* AFG: D3 This is already handled */
#endif

	{} /* terminator */
};
