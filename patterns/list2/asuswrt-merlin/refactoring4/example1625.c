#if !defined(__FreeBSD__) && !defined(AIX) && !defined(__OpenBSD__) && !defined(__DragonFly__)
if ((sys_stat(path, &S, false)<0)
      || (devnm(S_IFBLK, S.st_ex_dev, dev_disk, 256, 1)<0))
#else
  if ((sys_stat(path, &S, false)<0)
      || (devnm(S_IFBLK, S.st_ex_dev, dev_disk, 256, 0)<0))
	return (False);
