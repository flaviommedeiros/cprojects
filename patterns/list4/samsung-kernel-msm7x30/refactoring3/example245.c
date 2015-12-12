switch (temp) {
	case PIPE_INTERRUPT:
		phci_hcd_make_qtd(pehci_hcd, &urb_priv->qtd_list,	urb, &status);
		if (status < 0)	{
			return status;
		}
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
		qh = phci_hcd_submit_interrupt(pehci_hcd, ep, &urb_priv->qtd_list, urb,
			&status);
#else
		qh = phci_hcd_submit_interrupt(pehci_hcd, &urb_priv->qtd_list, urb,
			&status);
#endif
		if (status < 0)
			return status;
		break;

	case PIPE_CONTROL:
	case PIPE_BULK:

#ifdef THREAD_BASED
	spin_lock_irqsave (&pehci_hcd->lock, flags);
#endif
		phci_hcd_make_qtd(pehci_hcd, &qtd_list,	urb, &status);
		if (status < 0) {
			return status;
		}
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
		qh = phci_hcd_submit_async(pehci_hcd, ep, &qtd_list, urb,
			&status);
#else
		qh = phci_hcd_submit_async(pehci_hcd, &qtd_list, urb, &status);
#endif

#ifdef THREAD_BASED
	spin_unlock_irqrestore (&pehci_hcd->lock, flags);
#endif

		if (status < 0) {
			return status;
		}
		break;
#ifdef CONFIG_ISO_SUPPORT
	case PIPE_ISOCHRONOUS:
		iso_dbg(ISO_DBG_DATA,
			"[pehci_hcd_urb_enqueue]: URB Transfer buffer: 0x%08x\n",
			(long) urb->transfer_buffer);
		iso_dbg(ISO_DBG_DATA,
			"[pehci_hcd_urb_enqueue]: URB Buffer Length: %d\n",
			(long) urb->transfer_buffer_length);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
		phcd_submit_iso(pehci_hcd, ep, urb, (unsigned long *) &status);
#else
		spin_lock_irqsave(&pehci_hcd->lock, flags);
		phcd_store_urb_pending(pehci_hcd, 0, urb, (int *) &status);
		spin_unlock_irqrestore(&pehci_hcd->lock, flags);
#endif

		return status;

		break;
#endif
	default:
		return -ENODEV;
	}
