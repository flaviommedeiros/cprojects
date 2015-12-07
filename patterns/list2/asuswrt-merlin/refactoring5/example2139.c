#ifdef CONFIG_COMPAT
if (compat)
		ret = compat_rw_copy_check_uvector(type,
				(struct compat_iovec __user *)kiocb->ki_buf,
				kiocb->ki_nbytes, 1, &kiocb->ki_inline_vec,
				&kiocb->ki_iovec);
	else
#endif
		ret = rw_copy_check_uvector(type,
				(struct iovec __user *)kiocb->ki_buf,
				kiocb->ki_nbytes, 1, &kiocb->ki_inline_vec,
				&kiocb->ki_iovec);
