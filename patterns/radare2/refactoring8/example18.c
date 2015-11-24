static io_backend_t *io_backends[] = {
//#if __WIN32__ || __CYGWIN__ || MINGW32
//#warning TODO: add proper IO backend for windows here
//#else
	&iob_pipe,
//#endif
	NULL,
};
