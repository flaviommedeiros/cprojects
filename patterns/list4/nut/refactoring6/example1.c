if (ipmi_sdr_cache_create (sdr_ctx,
				 ipmi_ctx, CACHE_LOCATION,
				 IPMI_SDR_CACHE_CREATE_FLAGS_DEFAULT,
#ifndef HAVE_FREEIPMI_11X_12X
				 IPMI_SDR_CACHE_VALIDATION_FLAGS_DEFAULT,
#endif
				 NULL, NULL) < 0)
		{
			libfreeipmi_cleanup();
			fatal_with_errno(EXIT_FAILURE, "ipmi_sdr_cache_create: %s",
				ipmi_sdr_ctx_errormsg (sdr_ctx));
		}
