#ifdef VMXNET3_RSS
if (enable_mq)
		num_rx_queues = min(VMXNET3_DEVICE_MAX_RX_QUEUES,
				    (int)num_online_cpus());
	else
#endif
		num_rx_queues = 1;
