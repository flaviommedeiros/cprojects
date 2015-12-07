#if defined(_CFE_)
if (intstatus & ~(I_RDU | I_RFO) & I_ERRORS)
#else
	if (intstatus & I_ERRORS)
#endif
		events |= INTR_ERROR;
