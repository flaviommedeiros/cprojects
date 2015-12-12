#ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
if (unlikely((unsigned long)buf & 0x3)) {
		while (cnt >= 4) {
			u32 aligned_buf[32];
			int len = min(cnt & -4, (int)sizeof(aligned_buf));
			int items = len >> 2;
			int i;
			/* memcpy from input buffer into aligned buffer */
			memcpy(aligned_buf, buf, len);
			buf += len;
			cnt -= len;
			/* push data from aligned buffer into fifo */
			for (i = 0; i < items; ++i)
				mci_writel(host, DATA(host->data_offset),
						aligned_buf[i]);
		}
	} else
#endif
	{
		u32 *pdata = buf;
		for (; cnt >= 4; cnt -= 4)
			mci_writel(host, DATA(host->data_offset), *pdata++);
		buf = pdata;
	}
