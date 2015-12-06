#ifdef USE_SCRYPT
if (kernelinfo->interface == KL_SCRYPT)
	{
		sprintf(numbuf, "lg%utc%u", data->lookup_gap, (unsigned int)data->thread_concurrency);
		strcat(binaryfilename, numbuf);
	}
	else
#endif
	{
		sprintf(numbuf, "v%d", clState->vwidth);
		strcat(binaryfilename, numbuf);
	}
