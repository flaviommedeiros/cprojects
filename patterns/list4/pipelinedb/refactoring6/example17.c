if (errno == EEXIST || errno == EACCES
#ifdef EIDRM
					|| errno == EIDRM
#endif
					)
					return NULL;
