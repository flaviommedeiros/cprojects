#ifndef PRINTER_SUPPORT
if (1) {
	} else
#endif
	if (StrCaseCmp(rpcsrv_type, "embedded") == 0) {
		spoolss_cb.init         = spoolss_init_cb;
		spoolss_cb.shutdown     = spoolss_shutdown_cb;
		spoolss_cb.private_data = ep_ctx;
		if (!NT_STATUS_IS_OK(rpc_spoolss_init(&spoolss_cb))) {
			return false;
		}
	} else if (StrCaseCmp(rpcsrv_type, "daemon") == 0 ||
		   StrCaseCmp(rpcsrv_type, "external") == 0) {
		if (!NT_STATUS_IS_OK(rpc_spoolss_init(NULL))) {
			return false;
		}
	}
