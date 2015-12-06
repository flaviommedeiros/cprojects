static int bitmain_send_data(const uint8_t *data, int datalen, __maybe_unused struct cgpu_info *bitmain)
{
	int ret, ep = 0;
	//int delay;
	//struct bitmain_info *info = NULL;
	//cgtimer_t ts_start;

	if (datalen <= 0) {
		return 0;
	}

#if (defined(USE_ANT_S1) || defined(USE_ANT_S3))
	ep = C_BITMAIN_SEND;
	if (data[0] == BITMAIN_TOKEN_TYPE_TXCONFIG) {
		ep = C_BITMAIN_TOKEN_TXCONFIG;
	} else if (data[0] == BITMAIN_TOKEN_TYPE_TXTASK) {
		ep = C_BITMAIN_TOKEN_TXTASK;
	} else if (data[0] == BITMAIN_TOKEN_TYPE_RXSTATUS) {
		ep = C_BITMAIN_TOKEN_RXSTATUS;
	}
#endif

	//info = bitmain->device_data;
	//delay = datalen * 10 * 1000000;
	//delay = delay / info->baud;
	//delay += 4000;

	if (opt_debug) {
		applog(LOG_DEBUG, "%s: Sent(%d):", ANTDRV.dname, datalen);
		hexdump(data, datalen);
	}

	//cgsleep_prepare_r(&ts_start);
	applog(LOG_DEBUG, "%s: %s() start", ANTDRV.dname, __func__);
	ret = bitmain_write(bitmain, (char *)data, datalen, ep);
	applog(LOG_DEBUG, "%s: %s() stop ret=%d datalen=%d",
			  ANTDRV.dname, __func__, ret, datalen);
	//cgsleep_us_r(&ts_start, delay);

	//applog(LOG_DEBUG, "BitMain: Sent: Buffer delay: %dus", delay);

	return ret;
}
