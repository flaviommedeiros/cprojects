#if defined(CDROMCLOSETRAY) || defined(CDIOCCLOSE)
if (status != 0)
		err(EXIT_FAILURE, _("CD-ROM tray close command failed"));
