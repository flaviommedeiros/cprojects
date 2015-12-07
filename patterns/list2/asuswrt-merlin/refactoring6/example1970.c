if (is_block && atoi(getenv("MAJOR") ? : "0") == USB_DISK_MAJOR
#if (!defined(LINUX30) && LINUX_VERSION_CODE < KERNEL_VERSION(2,6,36))
		&& strcmp(getenv("PHYSDEVBUS") ? : "", "scsi") == 0
#endif
		)
	{
		/* scsi partition */
		char devname[64], fsck_log_name[64];
		int lock;

		sprintf(devname, "/dev/%s", device);
		lock = file_lock("usb");
		if (add) {
			if (nvram_get_int("usb_storage") && nvram_get_int("usb_automount")) {
				int minor = atoi(getenv("MINOR") ? : "0");
				if ((minor % 16) == 0 && !is_no_partition(device)) {
					/* This is a disc, and not a "no-partition" device,
					 * like APPLE iPOD shuffle. We can't mount it.
					 */
					file_unlock(lock);
					return;
				}
				TRACE_PT(" mount to dev: %s\n", devname);
				if (mount_partition(devname, host, NULL, device, EFH_HP_ADD)) {
_dprintf("restart_nas_services(%d): test 5.\n", getpid());
					//restart_nas_services(1, 1); // restart all NAS applications
					notify_rc_and_wait("restart_nasapps");
				}
				TRACE_PT(" end of mount\n");
			}
		}
		else {
			/* When unplugged, unmount the device even if usb storage is disabled in the GUI */
			umount_partition(devname, host, NULL, device, EFH_HP_REMOVE);
			/* Restart NAS applications (they could be killed by umount_mountpoint),
			 * or just re-read the configuration.
			 */

			snprintf(fsck_log_name, sizeof(fsck_log_name), "/tmp/fsck_ret/%s.0", device);
			unlink(fsck_log_name);
			snprintf(fsck_log_name, sizeof(fsck_log_name), "/tmp/fsck_ret/%s.log", device);
			unlink(fsck_log_name);
_dprintf("restart_nas_services(%d): test 6.\n", getpid());
			//restart_nas_services(1, 1);
			notify_rc_after_wait("restart_nasapps");
		}
		file_unlock(lock);
	}
#endif
	else if (strncmp(interface ? : "", "8/", 2) == 0) {	/* usb storage */
		run_nvscript("script_usbhotplug", NULL, 2);
#ifndef LINUX26
		hotplug_usb_storage_device(host, add, (add ? EFH_HP_ADD : EFH_HP_REMOVE) | (host < 0 ? EFH_HUNKNOWN : 0));
#endif
	}
	else {	/* It's some other type of USB device, not storage. */
#ifdef LINUX26
		if (is_block) return;
#endif
		/* Do nothing.  The user's hotplug script must do it all. */
		run_nvscript("script_usbhotplug", NULL, 2);
	}
