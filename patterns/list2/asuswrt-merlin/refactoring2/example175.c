#ifndef USB_TRACE
if (status && status != -ESHUTDOWN)
#endif
		VDBG(dev, "complete %s req %p stat %d len %u/%u\n",
			ep->ep.name, &req->req, status,
			req->req.actual, req->req.length);
