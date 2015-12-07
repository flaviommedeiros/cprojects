if (ic_myaddr == NONE ||
#ifdef CONFIG_ROOT_NFS
	    (root_server_addr == NONE &&
	     ic_servaddr == NONE &&
	     ROOT_DEV == Root_NFS) ||
#endif
	    ic_first_dev->next) {
#ifdef IPCONFIG_DYNAMIC
		if (ic_dynamic() < 0) {
			ic_close_devs();

			/*
			 * I don't know why, but sometimes the
			 * eepro100 driver (at least) gets upset and
			 * doesn't work the first time it's opened.
			 * But then if you close it and reopen it, it
			 * works just fine.  So we need to try that at
			 * least once before giving up.
			 *
			 * Also, if the root will be NFS-mounted, we
			 * have nowhere to go if DHCP fails.  So we
			 * just have to keep trying forever.
			 *
			 * 				-- Chip
			 */
#ifdef CONFIG_ROOT_NFS
			if (ROOT_DEV ==  Root_NFS) {
				printk(KERN_ERR
					"IP-Config: Retrying forever (NFS root)...\n");
				goto try_try_again;
			}
#endif

			if (--retries) {
				printk(KERN_ERR
				       "IP-Config: Reopening network devices...\n");
				goto try_try_again;
			}

			/* Oh, well.  At least we tried. */
			printk(KERN_ERR "IP-Config: Auto-configuration of network failed.\n");
			return -1;
		}
#else /* !DYNAMIC */
		printk(KERN_ERR "IP-Config: Incomplete network configuration information.\n");
		ic_close_devs();
		return -1;
#endif /* IPCONFIG_DYNAMIC */
	} else {
		/* Device selected manually or only one device -> use it */
		ic_dev = ic_first_dev->dev;
	}
