#ifdef _WIN32
if(((sig == SIGINT || sig == SIGTERM) && gc_enable == 1) ||
		(!(sig == SIGINT || sig == SIGTERM) && gc_enable == 0)) {
#else
	if(((sig == SIGINT || sig == SIGTERM || sig == SIGTSTP) && gc_enable == 1) ||
		(!(sig == SIGINT || sig == SIGTERM || sig == SIGTSTP) && gc_enable == 0)) {
#endif
		if(sig == SIGINT) {
			logprintf(LOG_DEBUG, "received interrupt signal, stopping pilight...");
		} else if(sig == SIGTERM) {
			logprintf(LOG_DEBUG, "received terminate signal, stopping pilight...");
		} else {
			logprintf(LOG_DEBUG, "received stop signal, stopping pilight...");
		}
		if(config_get_file() != NULL && gc_enable == 1) {
			gc_enable = 0;
			if(pilight.runmode == STANDALONE) {
				config_write(1, "all");
			}
		}
		gc_enable = 0;
		gc_run();
	}
}
