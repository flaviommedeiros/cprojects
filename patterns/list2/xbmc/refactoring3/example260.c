switch(request)
    {
      case PM_REQ_RATE:
	i = *(int *)arg; /* sample rate in and out */
	if(ioctl(dpm.fd, SNDCTL_DSP_SPEED, &i) < 0)
	    return -1;
	play_mode->rate = i;
	return 0;

      case PM_REQ_GETQSIZ:
	if(total_bytes <= 0)
	    return -1;
	*((int *)arg) = total_bytes;
	return 0;

#ifdef SNDCTL_DSP_GETODELAY
      case PM_REQ_DISCARD:
	output_counter = 0;
	return ioctl(dpm.fd, SNDCTL_DSP_RESET, NULL);

      case PM_REQ_FLUSH:
	output_counter = 0;
	return ioctl(dpm.fd, SNDCTL_DSP_SYNC, NULL);

      case PM_REQ_GETFILLED:
	if(total_bytes <= 0 || ioctl(dpm.fd, SNDCTL_DSP_GETODELAY, &i) == -1)
	    return -1;
	if (i > total_bytes) i = total_bytes;
	if(!(dpm.encoding & PE_MONO)) i >>= 1;
	if(dpm.encoding & PE_16BIT) i >>= 1;
	*((int *)arg) = i;
	return 0;

      case PM_REQ_GETFILLABLE:
	if(total_bytes <= 0 || ioctl(dpm.fd, SNDCTL_DSP_GETODELAY, &i) == -1)
	    return -1;
	if (i > total_bytes) i = 0;
        else i = total_bytes - i;
	if(!(dpm.encoding & PE_MONO)) i >>= 1;
	if(dpm.encoding & PE_16BIT) i >>= 1;
	*((int *)arg) = i;
	return 0;

      case PM_REQ_GETSAMPLES:
	if(ioctl(dpm.fd, SNDCTL_DSP_GETODELAY, &i) == -1)
	    return -1;
	i = output_counter - i;
	if(!(dpm.encoding & PE_MONO)) i >>= 1;
	if(dpm.encoding & PE_16BIT) i >>= 1;
	*((int *)arg) = i;
	return 0;

#else /* SNDCTL_DSP_GETODELAY */
      case PM_REQ_DISCARD:
	if(ioctl(dpm.fd, SNDCTL_DSP_RESET, NULL) == -1)
	    return -1;
	if(ioctl(dpm.fd, SNDCTL_DSP_GETOPTR, &cinfo) == -1)
	    return -1;
	output_counter = cinfo.bytes;
	return 0;

      case PM_REQ_FLUSH:
	if(ioctl(dpm.fd, SNDCTL_DSP_SYNC, NULL) == -1)
	    return -1;
	if(ioctl(dpm.fd, SNDCTL_DSP_GETOPTR, &cinfo) == -1)
	    return -1;
	output_counter = cinfo.bytes;
	return 0;

# ifdef SNDCTL_DSP_GETOSPACE
      case PM_REQ_GETFILLABLE:
	if(total_bytes <= 0 || ioctl(dpm.fd, SNDCTL_DSP_GETOSPACE, &info) == -1)
	    return -1;
	if (info.bytes > total_bytes) i = total_bytes;
	else i = info.bytes;
	if(!(dpm.encoding & PE_MONO)) i >>= 1;
	if(dpm.encoding & PE_16BIT) i >>= 1;
	*((int *)arg) = i;
	return 0;

      case PM_REQ_GETFILLED:
	if(total_bytes <= 0 || ioctl(dpm.fd, SNDCTL_DSP_GETOSPACE, &info) == -1)
	    return -1;
	if (info.bytes > total_bytes) i = 0;
	else i = total_bytes - info.bytes;
	if(!(dpm.encoding & PE_MONO)) i >>= 1;
	if(dpm.encoding & PE_16BIT) i >>= 1;
	*((int *)arg) = i;
	return 0;
# endif /* SNDCTL_DSP_GETOSPACE */

      case PM_REQ_GETSAMPLES:
	if(ioctl(dpm.fd, SNDCTL_DSP_GETOPTR, &cinfo) == -1)
	    return -1;
	i = cinfo.bytes - output_counter;
	if(!(dpm.encoding & PE_MONO)) i >>= 1;
	if(dpm.encoding & PE_16BIT) i >>= 1;
	*((int *)arg) = i;
	return 0;
#endif /* SNDCTL_DSP_GETODELAY */
    }
