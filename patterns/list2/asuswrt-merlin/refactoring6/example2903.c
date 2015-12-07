if (!pdev ||
#ifdef CONFIG_MACH_TX49XX
		    platform_device_add_resources(pdev, chan_res,
						  ARRAY_SIZE(chan_res)) ||
#endif
		    platform_device_add_data(pdev, &cpdata, sizeof(cpdata)) ||
		    platform_device_add(pdev))
			platform_device_put(pdev);
