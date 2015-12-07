#ifdef REGISTRY_BACKEND
if (!lp_config_backend_is_registry())
#endif
	{
		libnetapi_set_error_string(ctx,
			"Configuration manipulation requested but not "
			"supported by backend");
		return WERR_NOT_SUPPORTED;
	}
