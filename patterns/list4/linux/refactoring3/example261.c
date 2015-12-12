switch (cd->vendor) {

	case VENDOR_SCSI3:
		cgc.cmd[0] = READ_TOC;
		cgc.cmd[8] = 12;
		cgc.cmd[9] = 0x40;
		cgc.buffer = buffer;
		cgc.buflen = 12;
		cgc.quiet = 1;
		cgc.data_direction = DMA_FROM_DEVICE;
		cgc.timeout = VENDOR_TIMEOUT;
		rc = sr_do_ioctl(cd, &cgc);
		if (rc != 0)
			break;
		if ((buffer[0] << 8) + buffer[1] < 0x0a) {
			sr_printk(KERN_INFO, cd, "Hmm, seems the drive "
			   "doesn't support multisession CD's\n");
			no_multi = 1;
			break;
		}
		sector = buffer[11] + (buffer[10] << 8) +
		    (buffer[9] << 16) + (buffer[8] << 24);
		if (buffer[6] <= 1) {
			/* ignore sector offsets from first track */
			sector = 0;
		}
		break;

#ifdef CONFIG_BLK_DEV_SR_VENDOR
	case VENDOR_NEC:{
			unsigned long min, sec, frame;
			cgc.cmd[0] = 0xde;
			cgc.cmd[1] = 0x03;
			cgc.cmd[2] = 0xb0;
			cgc.buffer = buffer;
			cgc.buflen = 0x16;
			cgc.quiet = 1;
			cgc.data_direction = DMA_FROM_DEVICE;
			cgc.timeout = VENDOR_TIMEOUT;
			rc = sr_do_ioctl(cd, &cgc);
			if (rc != 0)
				break;
			if (buffer[14] != 0 && buffer[14] != 0xb0) {
				sr_printk(KERN_INFO, cd, "Hmm, seems the cdrom "
					  "doesn't support multisession CD's\n");

				no_multi = 1;
				break;
			}
			min = bcd2bin(buffer[15]);
			sec = bcd2bin(buffer[16]);
			frame = bcd2bin(buffer[17]);
			sector = min * CD_SECS * CD_FRAMES + sec * CD_FRAMES + frame;
			break;
		}

	case VENDOR_TOSHIBA:{
			unsigned long min, sec, frame;

			/* we request some disc information (is it a XA-CD ?,
			 * where starts the last session ?) */
			cgc.cmd[0] = 0xc7;
			cgc.cmd[1] = 0x03;
			cgc.buffer = buffer;
			cgc.buflen = 4;
			cgc.quiet = 1;
			cgc.data_direction = DMA_FROM_DEVICE;
			cgc.timeout = VENDOR_TIMEOUT;
			rc = sr_do_ioctl(cd, &cgc);
			if (rc == -EINVAL) {
				sr_printk(KERN_INFO, cd, "Hmm, seems the drive "
					  "doesn't support multisession CD's\n");
				no_multi = 1;
				break;
			}
			if (rc != 0)
				break;
			min = bcd2bin(buffer[1]);
			sec = bcd2bin(buffer[2]);
			frame = bcd2bin(buffer[3]);
			sector = min * CD_SECS * CD_FRAMES + sec * CD_FRAMES + frame;
			if (sector)
				sector -= CD_MSF_OFFSET;
			sr_set_blocklength(cd, 2048);
			break;
		}

	case VENDOR_WRITER:
		cgc.cmd[0] = READ_TOC;
		cgc.cmd[8] = 0x04;
		cgc.cmd[9] = 0x40;
		cgc.buffer = buffer;
		cgc.buflen = 0x04;
		cgc.quiet = 1;
		cgc.data_direction = DMA_FROM_DEVICE;
		cgc.timeout = VENDOR_TIMEOUT;
		rc = sr_do_ioctl(cd, &cgc);
		if (rc != 0) {
			break;
		}
		if ((rc = buffer[2]) == 0) {
			sr_printk(KERN_WARNING, cd,
				  "No finished session\n");
			break;
		}
		cgc.cmd[0] = READ_TOC;	/* Read TOC */
		cgc.cmd[6] = rc & 0x7f;	/* number of last session */
		cgc.cmd[8] = 0x0c;
		cgc.cmd[9] = 0x40;
		cgc.buffer = buffer;
		cgc.buflen = 12;
		cgc.quiet = 1;
		cgc.data_direction = DMA_FROM_DEVICE;
		cgc.timeout = VENDOR_TIMEOUT;
		rc = sr_do_ioctl(cd, &cgc);
		if (rc != 0) {
			break;
		}
		sector = buffer[11] + (buffer[10] << 8) +
		    (buffer[9] << 16) + (buffer[8] << 24);
		break;
#endif				/* CONFIG_BLK_DEV_SR_VENDOR */

	default:
		/* should not happen */
		sr_printk(KERN_WARNING, cd,
			  "unknown vendor code (%i), not initialized ?\n",
			  cd->vendor);
		sector = 0;
		no_multi = 1;
		break;
	}
