#ifdef SNDCTL_DSP_GETOSPACE
if(ioctl(fd, SNDCTL_DSP_GETOSPACE, &info) != -1) {
	total_bytes = info.fragstotal * info.fragsize;
	ctl->cmsg(CMSG_INFO, VERB_NOISY, "Audio device buffer: %d x %d bytes",
		  info.fragstotal, info.fragsize);
    }
    else
#endif /* SNDCTL_DSP_GETOSPACE */
	total_bytes = -1;
