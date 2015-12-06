switch (kernelinfo->interface)
	{
		case KL_NONE:
			applog(LOG_ERR, "%s: Failed to identify kernel interface for %s",
			       cgpu->dev_repr, kernel_file);
			free(source);
			return false;
#ifdef USE_SHA256D
		case KL_PHATK:
			if ((strstr(vbuff, "844.4") || strstr(vbuff, "851.4") ||
			     strstr(vbuff, "831.4") || strstr(vbuff, "898.1") ||
			     strstr(vbuff, "923.1") || strstr(vbuff, "938.2") ||
			     strstr(vbuff, "1113.2"))) {
				applog(LOG_WARNING, "WARNING: You have selected the phatk kernel.");
				applog(LOG_WARNING, "You are running SDK 2.6+ which performs poorly with this kernel.");
				applog(LOG_WARNING, "Downgrade your SDK and delete any .bin files before starting again.");
				applog(LOG_WARNING, "Or allow BFGMiner to automatically choose a more suitable kernel.");
			}
#endif
		default:
			;
	}
