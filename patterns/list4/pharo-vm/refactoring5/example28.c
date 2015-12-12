#ifdef MODET
if (TFLAG)
		/* ARMul_R15Altered would have to support it.  */
		abort ();
	else
#endif
		src &= 0xfffffffc;
