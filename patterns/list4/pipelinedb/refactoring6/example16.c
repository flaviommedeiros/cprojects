if (shmget_errno == EEXIST || shmget_errno == EACCES
#ifdef EIDRM
			|| shmget_errno == EIDRM
#endif
			)
			return NULL;
