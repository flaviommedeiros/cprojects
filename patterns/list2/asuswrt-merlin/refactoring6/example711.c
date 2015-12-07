if(major != USB_DISK_MAJOR
#ifdef BCM_MMC
				&& major != MMC_DISK_MAJOR
#endif
				)
			continue;
