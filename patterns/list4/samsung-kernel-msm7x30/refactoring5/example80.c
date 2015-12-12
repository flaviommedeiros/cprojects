#ifdef CONFIG_BCM4329
if (host->card && msmhost && msmhost->pdev_id == 1)
			printk(KERN_INFO"%s(): WLAN SKIP DETECT CHANGE\n",
					__func__);
		else
#endif
		mmc_detect_change(host, 0);
