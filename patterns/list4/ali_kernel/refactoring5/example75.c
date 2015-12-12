#ifdef CONFIG_CARDBUS
if (s->state & SOCKET_CARDBUS) {
	struct pci_dev *dev = s->cb_dev;
	u_int ptr;
	pci_bus_read_config_dword(dev->subordinate, 0, PCI_CARDBUS_CIS, &ptr);
	tuple->CISOffset = ptr & ~7;
	SPACE(tuple->Flags) = (ptr & 7);
    } else
#endif
    {
	/* Assume presence of a LONGLINK_C to address 0 */
	tuple->CISOffset = tuple->LinkOffset = 0;
	SPACE(tuple->Flags) = HAS_LINK(tuple->Flags) = 1;
    }
