if (saved_errno == EEXIST || saved_errno == EACCES
#ifdef EIDRM
			|| saved_errno == EIDRM
#endif
			)
			return -1;
