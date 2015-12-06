#if HAVE_VARNISH_V3
if (VSC_Open (vd, /* diag = */ 1))
#else /* if HAVE_VARNISH_V4 */
	if (VSM_Open (vd))
#endif
	{
		VSM_Delete (vd);
		ERROR ("varnish plugin: Unable to open connection.");

		return (-1);
	}
