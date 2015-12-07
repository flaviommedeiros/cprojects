#ifdef USE_RBPS
if (iov->iov_base & RBP_SMALLBUF)
				rbp = &he_dev->rbps_base[RBP_INDEX(iov->iov_base)];
			else
#endif
				rbp = &he_dev->rbpl_base[RBP_INDEX(iov->iov_base)];
