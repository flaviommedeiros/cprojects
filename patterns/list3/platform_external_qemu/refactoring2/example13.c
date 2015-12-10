#if HAVE_DLVSYM
if (!*alsa_functions[i].func)
#endif
				*alsa_functions[i].func = dlsym(alsa_handle,alsa_functions[i].name);
