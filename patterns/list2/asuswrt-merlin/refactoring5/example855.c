#ifdef	CONFIG_USB_OTG
if (hcd->self.otg_port == (wIndex + 1)
					&& hcd->self.b_hnp_enable)
				start_hnp(ohci);
			else
#endif
			ohci_writel (ohci, RH_PS_PSS,
				&ohci->regs->roothub.portstatus [wIndex]);
