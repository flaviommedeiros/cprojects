#ifdef EXT2_IMMUTABLE_FL
if (ioctl(myfd, EXT2_IOC_GETFLAGS, &oldflags) < 0)
		goto fail;
