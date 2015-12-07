#ifdef CONFIG_DEBUG_SYSLOG
if (wpa_debug_syslog) {
			vsyslog(syslog_priority(level), fmt, ap);
		} else {
#endif /* CONFIG_DEBUG_SYSLOG */
		wpa_debug_print_timestamp();
#ifdef CONFIG_DEBUG_FILE
		if (out_file) {
			vfprintf(out_file, fmt, ap);
			fprintf(out_file, "\n");
		} else {
#endif /* CONFIG_DEBUG_FILE */
		vprintf(fmt, ap);
		printf("\n");
#ifdef CONFIG_DEBUG_FILE
		}
#endif /* CONFIG_DEBUG_FILE */
#ifdef CONFIG_DEBUG_SYSLOG
		}
