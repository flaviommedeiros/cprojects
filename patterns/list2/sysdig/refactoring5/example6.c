#ifdef CONFIG_COMPAT
if (unlikely(args->compat)) {
		compat_iov = (const struct compat_iovec __user *)compat_ptr(val);
		res = compat_parse_readv_writev_bufs(args, compat_iov, iovcnt, args->consumer->snaplen, PRB_FLAG_PUSH_DATA | PRB_FLAG_IS_WRITE);
	} else
#endif
	{
		iov = (const struct iovec __user *)val;
		res = parse_readv_writev_bufs(args, iov, iovcnt, args->consumer->snaplen, PRB_FLAG_PUSH_DATA | PRB_FLAG_IS_WRITE);
	}
