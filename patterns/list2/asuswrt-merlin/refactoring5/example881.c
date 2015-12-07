#ifdef VELOCITY_ZERO_COPY_SUPPORT
if (skb_shinfo(skb)->nr_frags > 0) {
		int nfrags = skb_shinfo(skb)->nr_frags;
		tdinfo->skb = skb;
		if (nfrags > 6) {
			skb_copy_from_linear_data(skb, tdinfo->buf, skb->len);
			tdinfo->skb_dma[0] = tdinfo->buf_dma;
			td_ptr->tdesc0.pktsize =
			td_ptr->td_buf[0].pa_low = cpu_to_le32(tdinfo->skb_dma[0]);
			td_ptr->td_buf[0].pa_high = 0;
			td_ptr->td_buf[0].bufsize = td_ptr->tdesc0.pktsize;
			tdinfo->nskb_dma = 1;
			td_ptr->tdesc1.CMDZ = 2;
		} else {
			int i = 0;
			tdinfo->nskb_dma = 0;
			tdinfo->skb_dma[i] = pci_map_single(vptr->pdev, skb->data, skb->len - skb->data_len, PCI_DMA_TODEVICE);

			td_ptr->tdesc0.pktsize = pktlen;

			/* FIXME: support 48bit DMA later */
			td_ptr->td_buf[i].pa_low = cpu_to_le32(tdinfo->skb_dma);
			td_ptr->td_buf[i].pa_high = 0;
			td_ptr->td_buf[i].bufsize = skb->len->skb->data_len;

			for (i = 0; i < nfrags; i++) {
				skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
				void *addr = ((void *) page_address(frag->page + frag->page_offset));

				tdinfo->skb_dma[i + 1] = pci_map_single(vptr->pdev, addr, frag->size, PCI_DMA_TODEVICE);

				td_ptr->td_buf[i + 1].pa_low = cpu_to_le32(tdinfo->skb_dma[i + 1]);
				td_ptr->td_buf[i + 1].pa_high = 0;
				td_ptr->td_buf[i + 1].bufsize = frag->size;
			}
			tdinfo->nskb_dma = i - 1;
			td_ptr->tdesc1.CMDZ = i;
		}

	} else
#endif
	{
		/*
		 *	Map the linear network buffer into PCI space and
		 *	add it to the transmit ring.
		 */
		tdinfo->skb = skb;
		tdinfo->skb_dma[0] = pci_map_single(vptr->pdev, skb->data, pktlen, PCI_DMA_TODEVICE);
		td_ptr->tdesc0.pktsize = pktlen;
		td_ptr->td_buf[0].pa_low = cpu_to_le32(tdinfo->skb_dma[0]);
		td_ptr->td_buf[0].pa_high = 0;
		td_ptr->td_buf[0].bufsize = td_ptr->tdesc0.pktsize;
		tdinfo->nskb_dma = 1;
		td_ptr->tdesc1.CMDZ = 2;
	}
