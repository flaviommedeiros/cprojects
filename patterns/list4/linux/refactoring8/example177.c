static const struct ni_board_struct ni_boards[] = {
	{
		.name		= "DAQCard-ai-16xe-50",
		.device_id	= 0x010d,
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 1024,
		.gainlkup	= ai_gain_8,
		.ai_speed	= 5000,
		.caldac		= { dac8800, dac8043 },
	}, {
		.name		= "DAQCard-ai-16e-4",
		.device_id	= 0x010c,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 1024,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 4000,
		.caldac		= { mb88341 },		/* verified */
	}, {
		.name		= "DAQCard-6062E",
		.device_id	= 0x02c4,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 8192,
		.gainlkup	= ai_gain_16,
		.ai_speed	= 2000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 2048,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1176,
		.caldac		= { ad8804_debug },	/* verified */
	 }, {
		/* specs incorrect! */
		.name		= "DAQCard-6024E",
		.device_id	= 0x075e,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 1024,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1000000,
		.caldac		= { ad8804_debug },
	}, {
		/* specs incorrect! */
		.name		= "DAQCard-6036E",
		.device_id	= 0x0245,
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 1024,
		.alwaysdither	= 1,
		.gainlkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_range_table	= &range_bipolar10,
		.ao_speed	= 1000000,
		.caldac		= { ad8804_debug },
	 },
#if 0
	{
		.name		= "DAQCard-6715",
		.device_id	= 0x0000,	/* unknown */
		.n_aochan	= 8,
		.ao_maxdata	= 0x0fff,
		.ao_671x	= 8192,
		.caldac		= { mb88341, mb88341 },
	},
#endif
};
