if(ncap == NULL
#if 1
		/* Backward:
		 * This clause is for 'byte for byte'
		 * backward compatibility.
		 * Strickly speaking, it is 'bug for bug'.
		 */
		|| ncap->nelems == 0
#endif
		)
	{
		/*
		 * Handle empty netcdf
		 */
		const size_t nosz = 0;

		status = v1h_put_NCtype(psp, NC_UNSPECIFIED);
		if(status != ENOERR)
			return status;
		status = v1h_put_size_t(psp, &nosz);
		if(status != ENOERR)
			return status;
		return ENOERR;
	}
