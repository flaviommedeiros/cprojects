#if (__NetBSD__ || __OpenBSD__)
if (ret < 0 && errno != EINVAL)
#else
  if (ret < 0)
#endif
    USB_ERROR_STR(-errno, "error setting timeout: %s",
                  strerror(errno));
