#if defined(HAVE_LINUX_IF_BONDING_H) && \
	(defined(BOND_INFO_QUERY_OLD) || defined(SIOCBONDINFOQUERY))
if (ioctl(fd, SIOCBONDINFOQUERY, &ifr) == 0)
#else /* SIOCBONDINFOQUERY */
	if (ioctl(fd, BOND_INFO_QUERY_OLD, &ifr) == 0)
#endif /* SIOCBONDINFOQUERY */
		return 1;
