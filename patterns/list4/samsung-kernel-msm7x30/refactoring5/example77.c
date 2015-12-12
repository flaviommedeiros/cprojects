#ifndef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
if (unlikely((unsigned long)buf & 0x3)) {
		while (cnt >= 4) {
			/* pull data from fifo into aligned buffer */
			u32 aligned_buf[32];
			int len = min(cnt & -4, (int)sizeof(aligned_buf));
			int items = len >> 2;
			int i;
			for (i = 0; i < items; ++i)
				aligned_buf[i] = mci_readl(host,
						DATA(host->data_offset));
			/* memcpy from aligned buffer into output buffer */
			memcpy(buf, aligned_buf, len);
			buf += len;
			cnt -= len;
		}
	} else
#endif
	{
		u32 *pdata = buf;
		for (; cnt >= 4; cnt -= 4)
			*pdata++ = mci_readl(host, DATA(host->data_offset));
		buf = pdata;
	}
