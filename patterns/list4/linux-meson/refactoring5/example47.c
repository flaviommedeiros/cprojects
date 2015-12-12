#ifdef DWC_UTE_CFI
if (ep->dwc_ep.buff_mode != BM_STANDARD) {
			ep->dwc_ep.cfi_req_len = req->length;
			pcd->cfi->ops.build_descriptors(pcd->cfi, pcd, ep, req);
		} else {
#endif
			/* Setup and start the Transfer */
			if (req->dw_align_buf) {
				ep->dwc_ep.dma_addr = req->dw_align_buf_dma;
				ep->dwc_ep.start_xfer_buff = req->dw_align_buf;
				ep->dwc_ep.xfer_buff = req->dw_align_buf;
			} else {
				ep->dwc_ep.dma_addr = req->dma;
				ep->dwc_ep.start_xfer_buff = req->buf;
				ep->dwc_ep.xfer_buff = req->buf;
			}
			ep->dwc_ep.sent_zlp = 0;
			ep->dwc_ep.total_len = req->length;
			ep->dwc_ep.xfer_len = 0;
			ep->dwc_ep.xfer_count = 0;

			ep->dwc_ep.maxxfer = max_transfer;
			if (GET_CORE_IF(ep->pcd)->dma_desc_enable) {
				uint32_t out_max_xfer = DDMA_MAX_TRANSFER_SIZE
				    - (DDMA_MAX_TRANSFER_SIZE % 4);
				if (ep->dwc_ep.is_in) {
					if (ep->dwc_ep.maxxfer >
					    DDMA_MAX_TRANSFER_SIZE) {
						ep->dwc_ep.maxxfer =
						    DDMA_MAX_TRANSFER_SIZE;
					}
				} else {
					if (ep->dwc_ep.maxxfer > out_max_xfer) {
						ep->dwc_ep.maxxfer =
						    out_max_xfer;
					}
				}
			}
			if (ep->dwc_ep.maxxfer < ep->dwc_ep.total_len) {
				ep->dwc_ep.maxxfer -=
				    (ep->dwc_ep.maxxfer % ep->dwc_ep.maxpacket);
			}
			if (req->sent_zlp) {
				if ((ep->dwc_ep.total_len %
				     ep->dwc_ep.maxpacket == 0)
				    && (ep->dwc_ep.total_len != 0)) {
					ep->dwc_ep.sent_zlp = 1;
				}

			}
#ifdef DWC_UTE_CFI
		}
