#ifdef HAVE_OPENCL
if (options.gpu_devices->count && options.fork &&
			    strstr(alt->params.label, "-opencl"))
				*format = alt;
			else
#endif
			fmt_init(*format = alt);
