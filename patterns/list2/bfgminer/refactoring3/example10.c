switch (kernelinfo->interface)
	{
#ifdef USE_SCRYPT
		case KL_SCRYPT:
			if (!clState->padbufsize)
			{
				size_t ipt = (1024 / data->lookup_gap + (1024 % data->lookup_gap > 0));
				size_t bufsize = 128 * ipt * data->thread_concurrency;

				/* Use the max alloc value which has been rounded to a power of
				 * 2 greater >= required amount earlier */
				if (bufsize > data->max_alloc) {
					applog(LOG_WARNING, "Maximum buffer memory device %d supports says %lu", gpu, (unsigned long)data->max_alloc);
					applog(LOG_WARNING, "Your scrypt settings come to %lu", (unsigned long)bufsize);
				}
				applog(LOG_DEBUG, "Creating scrypt buffer sized %lu", (unsigned long)bufsize);
				clState->padbufsize = bufsize;

				/* This buffer is weird and might work to some degree even if
				 * the create buffer call has apparently failed, so check if we
				 * get anything back before we call it a failure. */
				clState->padbuffer8 = NULL;
				clState->padbuffer8 = clCreateBuffer(clState->context, CL_MEM_READ_WRITE, bufsize, NULL, &status);
				if (status != CL_SUCCESS && !clState->padbuffer8) {
					applog(LOG_ERR, "Error %d: clCreateBuffer (padbuffer8), decrease TC or increase LG", status);
					return false;
				}
			}
			// NOTE: fallthru
#endif
#ifdef USE_OPENCL_FULLHEADER
		case KL_FULLHEADER:
#endif
			if (!clState->CLbuffer0)
			{
				clState->CLbuffer0 = clCreateBuffer(clState->context, CL_MEM_READ_ONLY, MAX_CLBUFFER0_SZ, NULL, &status);
				if (status != CL_SUCCESS) {
					applog(LOG_ERR, "Error %d: clCreateBuffer (CLbuffer0)", status);
					return false;
				}
			}
			break;
		default:
			break;
	}
