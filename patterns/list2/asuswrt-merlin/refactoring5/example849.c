#ifndef SCI_ONLY
if (port->type == PORT_SCIF)
		count = scif_txroom(port);
	else
#endif
		count = sci_txroom(port);
