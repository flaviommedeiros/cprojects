#ifdef BIOCSETLIF
if (ioctl(fd, BIOCSETLIF, (caddr_t)&ifr) < 0)
#else
			if (ioctl(fd, BIOCSETIF, (caddr_t)&ifr) < 0)
#endif
			{
				status = check_setif_failure(p, errno);
				goto bad;
			}
