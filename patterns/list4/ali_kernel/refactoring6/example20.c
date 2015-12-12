if ((request->zero
						&& request->length
						&& (request->length
							% musb_ep->packet_sz)
							== 0)
#ifdef CONFIG_USB_INVENTRA_DMA
					|| (is_dma &&
						((!dma->desired_mode) ||
						    (request->actual &
						    (musb_ep->packet_sz - 1))))
#endif
				) {
					/* on dma completion, fifo may not
					 * be available yet ...
					 */
					if (csr & MUSB_TXCSR_TXPKTRDY)
						break;

					DBG(4, "sending zero pkt\n");
					musb_writew(epio, MUSB_TXCSR,
							MUSB_TXCSR_MODE
							| MUSB_TXCSR_TXPKTRDY);
					request->zero = 0;
				}
