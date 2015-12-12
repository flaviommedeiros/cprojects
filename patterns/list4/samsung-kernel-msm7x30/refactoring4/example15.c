#if defined(CUSTOMER_HW4)
if ((ret || ret == -ETIMEDOUT) && (dhd_pub->up))
#else
		if ((ret) && (dhd_pub->up))
#endif /* CUSTOMER_HW4 */
			/* Send hang event only if dhd_open() was success */
			dhd_os_check_hang(dhd_pub, ifindex, ret);
