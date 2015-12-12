void fhci_init_ep_registers(struct fhci_usb *usb, struct endpoint *ep,
			    enum fhci_mem_alloc data_mem)
{
	u8 rt;

	/* set the endpoint registers according to the endpoint */
	out_be16(&usb->fhci->regs->usb_ep[0],
		 USB_TRANS_CTR | USB_EP_MF | USB_EP_RTE);
	out_be16(&usb->fhci->pram->ep_ptr[0],
		 cpm_muram_offset(ep->ep_pram_ptr));

	rt = (BUS_MODE_BO_BE | BUS_MODE_GBL);
#ifdef MULTI_DATA_BUS
	if (data_mem == MEM_SECONDARY)
		rt |= BUS_MODE_DTB;
#endif
	out_8(&ep->ep_pram_ptr->rx_func_code, rt);
	out_8(&ep->ep_pram_ptr->tx_func_code, rt);
	out_be16(&ep->ep_pram_ptr->rx_buff_len, 1028);
	out_be16(&ep->ep_pram_ptr->rx_base, 0);
	out_be16(&ep->ep_pram_ptr->tx_base, cpm_muram_offset(ep->td_base));
	out_be16(&ep->ep_pram_ptr->rx_bd_ptr, 0);
	out_be16(&ep->ep_pram_ptr->tx_bd_ptr, cpm_muram_offset(ep->td_base));
	out_be32(&ep->ep_pram_ptr->tx_state, 0);
}
