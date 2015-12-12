if (dev &&
	    (!(dev->flags & IFF_UP) || (dev->type != ARPHRD_X25
#if IS_ENABLED(CONFIG_LLC)
					&& dev->type != ARPHRD_ETHER
#endif
					))){
		dev_put(dev);
		dev = NULL;
	}
