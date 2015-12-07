#ifdef SIOCGIFNUM
if (ioctl(ipfd, SIOCGIFNUM, &nif) < 0)
#endif
	nif = MAX_IFS;
