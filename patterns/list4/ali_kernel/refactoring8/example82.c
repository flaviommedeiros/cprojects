static const iw_handler		wavelan_private_handler[] =
{
	wavelan_set_qthr,		/* SIOCIWFIRSTPRIV */
	wavelan_get_qthr,		/* SIOCIWFIRSTPRIV + 1 */
#ifdef HISTOGRAM
	wavelan_set_histo,		/* SIOCIWFIRSTPRIV + 2 */
	wavelan_get_histo,		/* SIOCIWFIRSTPRIV + 3 */
#endif	/* HISTOGRAM */
};
