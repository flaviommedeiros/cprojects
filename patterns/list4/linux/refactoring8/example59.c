static struct uwb_est_entry i1480_est_fd00[] = {
	/* Anybody expecting this response has to use
	 * neh->extra_size to specify the real size that will
	 * come back. */
	[i1480_EVT_CONFIRM] = { .size = sizeof(struct i1480_evt_confirm) },
	[i1480_CMD_SET_IP_MAS] = { .size = sizeof(struct i1480_evt_confirm) },
#ifdef i1480_RCEB_EXTENDED
	[0x09] = {
		.size = sizeof(struct i1480_rceb),
		.offset = 1 + offsetof(struct i1480_rceb, wParamLength),
	},
#endif
};
