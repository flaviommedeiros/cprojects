#if HAVE_OPENCL
if (!(options.gpu_devices->count && options.fork &&
	      strstr(database.format->params.label, "-opencl")))
#endif
	fmt_init(database.format);
