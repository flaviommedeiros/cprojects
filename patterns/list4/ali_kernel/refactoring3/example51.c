switch(bay->state) {
	case mb_powering_up:
	    	if (bay->ops->setup_bus(bay, bay->last_value) < 0) {
			MBDBG("mediabay%d: device not supported (kind:%d)\n", i, bay->content_id);
	    		set_mb_power(bay, 0);
	    		break;
	    	}
	    	bay->timer = msecs_to_jiffies(MB_RESET_DELAY);
	    	bay->state = mb_enabling_bay;
		MBDBG("mediabay%d: enabling (kind:%d)\n", i, bay->content_id);
		break;
	case mb_enabling_bay:
		bay->ops->un_reset(bay);
	    	bay->timer = msecs_to_jiffies(MB_SETUP_DELAY);
	    	bay->state = mb_resetting;
		MBDBG("mediabay%d: waiting reset (kind:%d)\n", i, bay->content_id);
	    	break;
	case mb_resetting:
		if (bay->content_id != MB_CD) {
			MBDBG("mediabay%d: bay is up (kind:%d)\n", i, bay->content_id);
			bay->state = mb_up;
			break;
	    	}
#ifdef CONFIG_BLK_DEV_IDE_PMAC
		MBDBG("mediabay%d: waiting IDE reset (kind:%d)\n", i, bay->content_id);
		bay->ops->un_reset_ide(bay);
	    	bay->timer = msecs_to_jiffies(MB_IDE_WAIT);
	    	bay->state = mb_ide_resetting;
#else
		printk(KERN_DEBUG "media-bay %d is ide (not compiled in kernel)\n", i);
		set_mb_power(bay, 0);
#endif /* CONFIG_BLK_DEV_IDE_PMAC */
	    	break;
#ifdef CONFIG_BLK_DEV_IDE_PMAC
	case mb_ide_resetting:
	    	bay->timer = msecs_to_jiffies(MB_IDE_TIMEOUT);
	    	bay->state = mb_ide_waiting;
		MBDBG("mediabay%d: waiting IDE ready (kind:%d)\n", i, bay->content_id);
	    	break;
	case mb_ide_waiting:
		if (bay->cd_base == NULL) {
			bay->timer = 0;
			bay->state = mb_up;
			MBDBG("mediabay%d: up before IDE init\n", i);
			break;
		} else if (MB_IDE_READY(i)) {
			bay->timer = 0;
			bay->state = mb_up;
			if (bay->cd_index < 0) {
				printk("mediabay %d, registering IDE...\n", i);
				pmu_suspend();
				ide_port_scan(bay->cd_port);
				if (bay->cd_port->present)
					bay->cd_index = bay->cd_port->index;
				pmu_resume();
			}
			if (bay->cd_index == -1) {
				/* We eventually do a retry */
				bay->cd_retry++;
				printk("IDE register error\n");
				set_mb_power(bay, 0);
			} else {
				printk(KERN_DEBUG "media-bay %d is ide%d\n", i, bay->cd_index);
				MBDBG("mediabay %d IDE ready\n", i);
			}
			break;
	    	} else if (bay->timer > 0)
			bay->timer -= msecs_to_jiffies(MB_POLL_DELAY);
	    	if (bay->timer <= 0) {
			printk("\nIDE Timeout in bay %d !, IDE state is: 0x%02x\n",
			       i, readb(bay->cd_base + 0x70));
			MBDBG("mediabay%d: nIDE Timeout !\n", i);
			set_mb_power(bay, 0);
			bay->timer = 0;
	    	}
		break;
#endif /* CONFIG_BLK_DEV_IDE_PMAC */
	case mb_powering_down:
	    	bay->state = mb_empty;
#ifdef CONFIG_BLK_DEV_IDE_PMAC
    	        if (bay->cd_index >= 0) {
			printk(KERN_DEBUG "Unregistering mb %d ide, index:%d\n", i,
			       bay->cd_index);
			ide_port_unregister_devices(bay->cd_port);
			bay->cd_index = -1;
		}
	    	if (bay->cd_retry) {
			if (bay->cd_retry > MAX_CD_RETRIES) {
				/* Should add an error sound (sort of beep in dmasound) */
				printk("\nmedia-bay %d, IDE device badly inserted or unrecognised\n", i);
			} else {
				/* Force a new power down/up sequence */
				bay->content_id = MB_NO;
			}
	    	}
#endif /* CONFIG_BLK_DEV_IDE_PMAC */
		MBDBG("mediabay%d: end of power down\n", i);
	    	break;
	}
