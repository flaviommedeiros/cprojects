#ifdef USE_SCRYPT
if (kernelinfo->interface == KL_SCRYPT)
		sprintf(CompilerOptions, "-D LOOKUP_GAP=%d -D CONCURRENT_THREADS=%d -D WORKSIZE=%d",
			data->lookup_gap, (unsigned int)data->thread_concurrency, (int)kernelinfo->wsize);
	else
#endif
	{
		sprintf(CompilerOptions, "-D WORKSIZE=%d -D VECTORS%d -D WORKVEC=%d",
			(int)kernelinfo->wsize, clState->vwidth, (int)kernelinfo->wsize * clState->vwidth);
	}
