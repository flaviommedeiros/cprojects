#ifdef TITAN_GE_JUMBO_FRAMES
if ((titan_ge_init_rx_desc_ring
	    (titan_ge_eth, titan_ge_eth->rx_ring_size, TITAN_GE_JUMBO_BUFSIZE,
	     (unsigned long) titan_ge_eth->rx_desc_area, 0,
	      (unsigned long) titan_ge_eth->rx_dma)) == 0)
#else
	if ((titan_ge_init_rx_desc_ring
	     (titan_ge_eth, titan_ge_eth->rx_ring_size, TITAN_GE_STD_BUFSIZE,
	      (unsigned long) titan_ge_eth->rx_desc_area, 0,
	      (unsigned long) titan_ge_eth->rx_dma)) == 0)
#endif
		panic("%s: Error initializing RX Ring\n", netdev->name);
