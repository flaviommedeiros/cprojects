if (is_miracast_enabled(adapter->wfd_info.stack_wfd_mode)
		#ifdef CONFIG_CONCURRENT_MODE
		|| (adapter->pbuddy_adapter && is_miracast_enabled(adapter->pbuddy_adapter->wfd_info.stack_wfd_mode))
		#endif
	)
		miracast_enabled = _TRUE;
