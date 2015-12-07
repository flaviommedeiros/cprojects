#ifdef BCM_TSO
if (dev->features & NETIF_F_TSO) {
		printk(", TSO ON");
	}
	else
#endif
#ifdef BCM_NAPI_RXPOLL
	printk(", NAPI ON");
