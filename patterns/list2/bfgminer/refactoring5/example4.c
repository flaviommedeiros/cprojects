#ifdef USE_SCRYPT
if (malgo->algo == POW_SCRYPT)
		kernelinfo->wsize = 256;
	else
#endif
	if (strstr(name, "Tahiti"))
		kernelinfo->wsize = 64;
	else
		kernelinfo->wsize = (clState->max_work_size <= 256 ? clState->max_work_size : 256) / clState->vwidth;
