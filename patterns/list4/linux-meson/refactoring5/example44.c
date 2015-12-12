#ifdef DWC_EN_ISOC
if (dwc_ep->type ==
					    DWC_OTG_EP_TYPE_ISOC) {
						/*
						 * This checking is performed to prevent first "false" BNA
						 * handling occuring right after reconnect
						 */
						if (dwc_ep->next_frame !=
						    0xffffffff)
							dwc_otg_pcd_handle_iso_bna(ep);
					} else
#endif				/* DWC_EN_ISOC */
					{
						dwc_otg_pcd_handle_noniso_bna(ep);
					}
