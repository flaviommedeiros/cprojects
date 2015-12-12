switch (temp) {
	case PIPE_INTERRUPT:
		/*only one td */
		num_tds	= 1;
		mult = 1 + ((max >> 11)	& 0x03);
		max &= 0x07ff;
		max *= mult;

		if (urb->transfer_buffer_length	> max) {
			err("interrupt urb length is greater then %d\n", max);
			return -EINVAL;
		}

		if (hubdev && urb->dev->parent == usb_hcd->self.root_hub) {
			huburb = urb;
		}

		break;

	case PIPE_CONTROL:
		/*calculate the	number of tds, follow 1	pattern	*/
		if (No_Data_Phase && No_Status_Phase) {
			printk("Only SetUP Phase\n");
			num_tds	= (urb->transfer_buffer_length == 0) ? 1 :
				((urb->transfer_buffer_length -
				  1) / HC_ATL_PL_SIZE +	1);
		} else if (!No_Data_Phase && No_Status_Phase) {
			printk("SetUP Phase and	Data Phase\n");
			num_tds	= (urb->transfer_buffer_length == 0) ? 2 :
				((urb->transfer_buffer_length -
				  1) / HC_ATL_PL_SIZE +	3);
		} else if (!No_Data_Phase && !No_Status_Phase) {
			num_tds	= (urb->transfer_buffer_length == 0) ? 2 :
				((urb->transfer_buffer_length -
				  1) / HC_ATL_PL_SIZE +	3);
		}
		
		break;
		
	case PIPE_BULK:
		num_tds	=
			(urb->transfer_buffer_length - 1) / HC_ATL_PL_SIZE + 1;
		if ((urb->transfer_flags & URB_ZERO_PACKET)
			&& !(urb->transfer_buffer_length % max)) {
			num_tds++;
		}
		
		break;
		
#ifdef CONFIG_ISO_SUPPORT
	case PIPE_ISOCHRONOUS:
		/* Don't need to do anything here */
		break;
#endif
	default:
		return -EINVAL;	/*not supported	isoc transfers */


	}
