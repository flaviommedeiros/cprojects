#ifndef	OHCI_VERBOSE_DEBUG
if (status != 0)
#endif
	dbg("%s %p dev=%d ep=%d%s-%s flags=%x len=%d/%d stat=%d",
		    str,
		    urb,
		    usb_pipedevice (pipe),
		    usb_pipeendpoint (pipe),
		    usb_pipeout (pipe)? "out" : "in",
		    pipestring (pipe),
		    urb->transfer_flags,
		    urb->actual_length,
		    urb->transfer_buffer_length,
		    status);
