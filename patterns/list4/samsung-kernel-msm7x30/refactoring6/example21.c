if ((request->zero && request->length
			&& (request->length % musb_ep->packet_sz == 0)
			&& (request->actual == request->length))
#if defined(CONFIG_USB_INVENTRA_DMA) || defined(CONFIG_USB_UX500_DMA)
			|| (is_dma && (!dma->desired_mode ||
				(request->actual &
					(musb_ep->packet_sz - 1))))
#endif
		) {
			/*
			 * On DMA completion, FIFO may not be
			 * available yet...
			 */
			if (csr & MUSB_TXCSR_TXPKTRDY)
				return;

			dev_dbg(musb->controller, "sending zero pkt\n");
			musb_writew(epio, MUSB_TXCSR, MUSB_TXCSR_MODE
					| MUSB_TXCSR_TXPKTRDY);
			request->zero = 0;
		}
