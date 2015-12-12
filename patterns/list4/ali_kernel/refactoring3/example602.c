switch (devtype) {
	case ARPHRD_ETHER:
	case ARPHRD_LOOPBACK:
		return sizeof(struct ethhdr);
#ifdef CONFIG_TR
	case ARPHRD_IEEE802_TR:
		return sizeof(struct trh_hdr);
#endif
	}
