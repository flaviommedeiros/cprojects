#ifdef CONFIG_IP_MULTICAST
if (psf->sf_oldin &&
		    !IGMP_V1_SEEN(in_dev) && !IGMP_V2_SEEN(in_dev)) {
			psf->sf_crcount = in_dev->mr_qrv ?: sysctl_igmp_qrv;
			psf->sf_next = pmc->tomb;
			pmc->tomb = psf;
			rv = 1;
		} else
#endif
			kfree(psf);
