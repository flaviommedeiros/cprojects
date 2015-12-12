switch (usb_pipetype(urb->pipe)) {
	case PIPE_CONTROL:
	case PIPE_BULK:
	//	status = 0;
		qh = urb_priv->qh;
		if(qh==NULL)
			break;

		td_ptd_buf = &td_ptd_map_buff[TD_PTD_BUFF_TYPE_ATL];
		td_ptd_map = &td_ptd_buf->map_list[qh->qtd_ptd_index];

		/*if its already been removed */
		if (td_ptd_map->state == TD_PTD_NEW) {
			break;
		}
/* patch added for stopping Full speed PTD */
/* patch starts	ere */
		if (urb->dev->speed != USB_SPEED_HIGH) {

			cancel_qtd = td_ptd_map->qtd;
			if (!qh	|| !cancel_qtd)	{
				err("Never Error:QH and	QTD must not be	zero\n");
			} else {
				cancel_urb = cancel_qtd->urb;
				cancel_urb_priv	=
					(urb_priv_t *) cancel_urb->hcpriv;
				mem_addr = &cancel_qtd->mem_addr;
				qha = &atlqha;
				memset(qha, 0, sizeof(struct _isp1763_qha));

				skipmap	=
					isp1763_reg_read16(hcd->dev,
							   hcd->regs.
							   atltdskipmap,
							   skipmap);
				skipmap	|= td_ptd_map->ptd_bitmap;
				isp1763_reg_write16(hcd->dev,
						    hcd->regs.atltdskipmap,
						    skipmap);

				/*read this ptd	from the ram address,address is	in the
				   td_ptd_map->ptd_header_addr */
				isp1763_mem_read(hcd->dev,
						 td_ptd_map->ptd_header_addr, 0,
						 (u32 *) (qha),	PHCI_QHA_LENGTH,
						 0);
				if ((qha->td_info1 & QHA_VALID)
					|| (qha->td_info4 &	QHA_ACTIVE)) {

					qha->td_info2 |= 0x00008000;
					qha->td_info1 |= QHA_VALID;
					qha->td_info4 |= QHA_ACTIVE;
					skipmap	&= ~td_ptd_map->ptd_bitmap;
					ormask |= td_ptd_map->ptd_bitmap;
					isp1763_reg_write16(hcd->dev,
						hcd->regs.
						atl_irq_mask_or,
						ormask);
					/* copy back into the header, payload is	already
					 * present no need to write again */
					isp1763_mem_write(hcd->dev,
						td_ptd_map->
						ptd_header_addr, 0,
						(u32 *) (qha),
						PHCI_QHA_LENGTH, 0);
					/*unskip this td */
					isp1763_reg_write16(hcd->dev,
						hcd->regs.
						atltdskipmap,
						skipmap);
					udelay(100);
				}

				isp1763_mem_read(hcd->dev,
					td_ptd_map->ptd_header_addr, 0,
					(u32 *) (qha),	PHCI_QHA_LENGTH,
					0);
				if (!(qha->td_info1 & QHA_VALID)
					&& !(qha->td_info4 & QHA_ACTIVE)) {
					printk(KERN_NOTICE
					"ptd has	been retired \n");
				}

			}
		}

/*   Patch Ends	*/
		/* These TDs are not pending anymore */
		td_ptd_buf->pending_ptd_bitmap &= ~td_ptd_map->ptd_bitmap;

		/*tell atl worker this urb is going to be removed */
		td_ptd_map->state = TD_PTD_REMOVE;
		/* These TDs are not pending anymore */
		td_ptd_buf->pending_ptd_bitmap &= ~td_ptd_map->ptd_bitmap;
		/*tell atl worker this urb is going to be removed */
		td_ptd_map->state = TD_PTD_REMOVE;
		urb_priv->state	|= DELETE_URB;

		/*read the skipmap, to see if this transfer has	to be rescheduled */
		skipmap	=
			isp1763_reg_read16(hcd->dev, hcd->regs.atltdskipmap,
			skipmap);
		pehci_check("remove skip map %x, ptd map %x\n",	skipmap,
			td_ptd_map->ptd_bitmap);

		buffstatus =
			isp1763_reg_read16(hcd->dev, hcd->regs.buffer_status,
			buffstatus);


		isp1763_reg_write16(hcd->dev, hcd->regs.atltdskipmap,
			skipmap | td_ptd_map->ptd_bitmap);

		while (!(skipmap & td_ptd_map->ptd_bitmap)) {
			udelay(125);

			skipmap	= isp1763_reg_read16(hcd->dev,
				hcd->regs.atltdskipmap,
				skipmap);
		}

		/* if all  transfers skipped,
		 * then	disable	the atl	buffer,
		 * so that new transfer	can come in
		 * need	to see the side	effects
		 * */
		if (skipmap == NO_TRANSFER_ACTIVE) {
			/*disable the buffer */
			pehci_info("disable the	atl buffer\n");
			buffstatus &= ~ATL_BUFFER;
			isp1763_reg_write16(hcd->dev, hcd->regs.buffer_status,
				buffstatus);
		}

		qtd_list = &qh->qtd_list;
		/*this should remove all pending transfers */
		pehci_check("num tds %d, urb length %d,device %d\n",
			urb_priv->length, urb->transfer_buffer_length,
			urb->dev->devnum);

		pehci_check("remove first qtd address %p\n", urb_priv->qtd[0]);
		pehci_check("length of the urb %d, completed %d\n",
			urb->transfer_buffer_length, urb->actual_length);
		qtd = urb_priv->qtd[urb_priv->length - 1];
		pehci_check("qtd state is %x\n", qtd->state);


		urb->status=status;
		status = 0;
#ifdef USBNET 
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
		pehci_hcd_urb_delayed_complete(hcd, qh, urb, td_ptd_map, NULL);
#else
		pehci_hcd_urb_delayed_complete(hcd, qh, urb, td_ptd_map);
#endif
#else
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
		pehci_hcd_urb_complete(hcd, qh, urb, td_ptd_map, NULL);
#else
		pehci_hcd_urb_complete(hcd, qh, urb, td_ptd_map);
#endif

#endif
		break;

	case PIPE_INTERRUPT:
		pehci_check("phci_1763_urb_dequeue: INTR needs to be done\n");
		urb->status = status; //-ENOENT;//This will allow to suspend the system. in auto suspend mode
		status = 0;
		qh = urb_priv->qh;
		if(qh==NULL)
			break;

		td_ptd_buf = &td_ptd_map_buff[TD_PTD_BUFF_TYPE_INTL];
		td_ptd_map = &td_ptd_buf->map_list[qh->qtd_ptd_index];

		/*urb is already been removed */
		if (td_ptd_map->state == TD_PTD_NEW) {
			kfree(urb_priv);
			break;
		}

		/* These TDs are not pending anymore */
		td_ptd_buf->pending_ptd_bitmap &= ~td_ptd_map->ptd_bitmap;

		td_ptd_map->state = TD_PTD_REMOVE;
		urb_priv->state	|= DELETE_URB;

		/*read the skipmap, to see if this transfer has	to be rescheduled */
		skipmap	=
			isp1763_reg_read16(hcd->dev, hcd->regs.inttdskipmap,
			skipmap);

		isp1763_reg_write16(hcd->dev, hcd->regs.inttdskipmap,
			skipmap | td_ptd_map->ptd_bitmap);
		qtd_list = &qh->qtd_list;
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
		pehci_hcd_urb_complete(hcd, qh, urb, td_ptd_map, NULL);
#else
		pehci_hcd_urb_complete(hcd, qh, urb, td_ptd_map);
#endif
		break;
#ifdef CONFIG_ISO_SUPPORT
	case PIPE_ISOCHRONOUS:
		pehci_info("urb dequeue %x %x\n", urb,urb->pipe);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24)
	if(urb->dev->speed==USB_SPEED_HIGH){
		retval = usb_hcd_check_unlink_urb(usb_hcd, urb, status);
		if (!retval) {
			pehci_info("[pehci_hcd_urb_dequeue] usb_hcd_unlink_urb_from_ep with status = %d\n", status);
			usb_hcd_unlink_urb_from_ep(usb_hcd, urb);


		}
	}
#endif

		
		status = 0;
		ep=urb->ep;
		spin_unlock_irqrestore(&hcd->lock, flags);
		mdelay(100);


#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
						if (urb->hcpriv!= periodic_ep[0]){
#else
						if (urb->ep != periodic_ep[0]){
#endif
	if(!list_empty(&ep->urb_list)){	
		while(!list_empty(&ep->urb_list)){
			urb=container_of(ep->urb_list.next,struct urb,urb_list);
			pehci_info("list is not empty %x %x\n",urb,urb->dev->state);
			if(urb){
		retval = usb_hcd_check_unlink_urb(usb_hcd, urb,0);
		if (!retval) {
			pehci_info("[pehci_hcd_urb_dequeue] usb_hcd_unlink_urb_from_ep with status = %d\n", status);
			usb_hcd_unlink_urb_from_ep(usb_hcd, urb);
		}
			urb->status=-ESHUTDOWN;
	#if LINUX_VERSION_CODE <KERNEL_VERSION(2,6,24)
			usb_hcd_giveback_urb(usb_hcd,urb);
	#else
			usb_hcd_giveback_urb(usb_hcd,urb,urb->status);
	#endif
				
			}
		}
		}else{
	if(urb){
		pehci_info("list empty %x\n",urb->dev->state);
		phcd_clean_urb_pending(hcd, urb);
		retval = usb_hcd_check_unlink_urb(usb_hcd, urb,0);
		if (!retval) {
			pehci_info("[pehci_hcd_urb_dequeue] usb_hcd_unlink_urb_from_ep with status = %d\n", status);
			usb_hcd_unlink_urb_from_ep(usb_hcd, urb);
		}
			urb->status=-ESHUTDOWN;
	#if LINUX_VERSION_CODE <KERNEL_VERSION(2,6,24)
			usb_hcd_giveback_urb(usb_hcd,urb);
	#else
			usb_hcd_giveback_urb(usb_hcd,urb,urb->status);
	#endif
				
			}
			
		}
	}	
#endif
		return 0;
		/*nothing to do	here, wait till	all transfers are done in iso worker */
		break;
	}

	spin_unlock_irqrestore(&hcd->lock, flags);
	pehci_info("status %d\n", status);
	pehci_entry("--	%s: Exit\n", __FUNCTION__);
	return status;
}
