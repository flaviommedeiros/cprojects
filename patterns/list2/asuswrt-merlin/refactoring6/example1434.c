if (dev->type == ARPHRD_X25
#if defined(CONFIG_LLC) || defined(CONFIG_LLC_MODULE)
	 || dev->type == ARPHRD_ETHER
#endif
	 ) {
		switch (event) {
			case NETDEV_UP:
				x25_link_device_up(dev);
				break;
			case NETDEV_GOING_DOWN:
				nb = x25_get_neigh(dev);
				if (nb) {
					x25_terminate_link(nb);
					x25_neigh_put(nb);
				}
				break;
			case NETDEV_DOWN:
				x25_kill_by_device(dev);
				x25_route_device_down(dev);
				x25_link_device_down(dev);
				break;
		}
	}
