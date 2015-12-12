switch (sdl->sdl_type) {
#ifdef IFT_ECONET
	case IFT_ECONET:
		if (sdl->sdl_alen < 2)
			return EAI_FAMILY;
		if (CLLADDR(sdl)[1] == 0)
			n = snprintf(host, hostlen, "%u", CLLADDR(sdl)[0]);
		else
			n = snprintf(host, hostlen, "%u.%u",
			    CLLADDR(sdl)[1], CLLADDR(sdl)[0]);
		if (n < 0 || (socklen_t) n >= hostlen) {
			*host = '\0';
			return EAI_MEMORY;
		} else
			return 0;
#endif
	case IFT_IEEE1394:
		if (sdl->sdl_alen < sizeof(iha->iha_uid))
			return EAI_FAMILY;
		iha =
		    (const struct ieee1394_hwaddr *)(const void *)CLLADDR(sdl);
		return hexname(iha->iha_uid, sizeof(iha->iha_uid),
		    host, hostlen);
	/*
	 * The following have zero-length addresses.
	 * IFT_ATM	(net/if_atmsubr.c)
	 * IFT_FAITH	(net/if_faith.c)
	 * IFT_GIF	(net/if_gif.c)
	 * IFT_LOOP	(net/if_loop.c)
	 * IFT_PPP	(net/if_ppp.c, net/if_spppsubr.c)
	 * IFT_SLIP	(net/if_sl.c, net/if_strip.c)
	 * IFT_STF	(net/if_stf.c)
	 * IFT_L2VLAN	(net/if_vlan.c)
	 * IFT_PROPVIRTUAL (net/if_bridge.h>
	 */
	/*
	 * The following use IPv4 addresses as link-layer addresses:
	 * IFT_OTHER	(net/if_gre.c)
	 */
	case IFT_ARCNET: /* default below is believed correct for all these. */
	case IFT_ETHER:
	case IFT_FDDI:
	case IFT_HIPPI:
	case IFT_ISO88025:
	default:
		return hexname((const u_int8_t *)CLLADDR(sdl),
		    (size_t)sdl->sdl_alen, host, hostlen);
	}
