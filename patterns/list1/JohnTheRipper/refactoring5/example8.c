#ifdef DEBUG
if (format->params.flags & FMT_DYNAMIC) {
			// in debug mode, we 'allow' dyna
		} else
#else
		if (options.format &&
		    !strcasecmp(options.format, "dynamic-all") &&
		    (format->params.flags & FMT_DYNAMIC)) {
			// allow dyna if '-format=dynamic-all' was selected
		} else
#endif
		if (options.format &&
		    !strcasecmp(options.format, format->params.label)) {
			// allow if specifically requested
		} else
			return;
