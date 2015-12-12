#ifdef CONFIG_CONCURRENT_MODE
if (padapter->isprimary)
			reg_ifname = padapter->registrypriv.ifname;
		else
#endif
		reg_ifname = padapter->registrypriv.if2name;
