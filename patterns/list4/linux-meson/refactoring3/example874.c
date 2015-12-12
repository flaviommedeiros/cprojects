switch(brd.device_id){
		case PCI_DEVICE_ID_MP1 :
		case PCIE_DEVICE_ID_MP1 :
		case PCIE_DEVICE_ID_MP1E :
		case PCIE_DEVICE_ID_GT_MP1 :
			sbdev->nr_ports = 1;
			break;
		case PCI_DEVICE_ID_MP2 :
		case PCIE_DEVICE_ID_MP2 :
		case PCIE_DEVICE_ID_GT_MP2 :
		case PCIE_DEVICE_ID_MP2B :
		case PCIE_DEVICE_ID_MP2E :
			sbdev->nr_ports = 2;

			/* serial base address remap */
			if (sbdev->revision == 0xc0)
			{
				int prev_port_addr = 0;

				pci_read_config_dword(pcidev, PCI_BASE_ADDRESS_0, &prev_port_addr);
				pci_remap_base(pcidev, PCI_BASE_ADDRESS_1, prev_port_addr + 8, 8);
			}
			break;
		case PCI_DEVICE_ID_MP4 :
		case PCI_DEVICE_ID_MP4A :
		case PCIE_DEVICE_ID_MP4 :
		case PCI_DEVICE_ID_GT_MP4 :
		case PCI_DEVICE_ID_GT_MP4A :
		case PCIE_DEVICE_ID_GT_MP4 :
		case PCI_DEVICE_ID_MP4M :
		case PCIE_DEVICE_ID_MP4B :
			sbdev->nr_ports = 4;

			if(sbdev->revision == 0x91){
				sbdev->reserved_addr[0] = pcidev->resource[0].start & PCI_BASE_ADDRESS_IO_MASK;
				outb(0x03 , sbdev->reserved_addr[0] + 0x01);
				outb(0x03 , sbdev->reserved_addr[0] + 0x02);
				outb(0x01 , sbdev->reserved_addr[0] + 0x20);
				outb(0x00 , sbdev->reserved_addr[0] + 0x21);
				request_region(sbdev->reserved_addr[0], 32, sbdev->name);
				sbdev->uart_access_addr = pcidev->resource[1].start & PCI_BASE_ADDRESS_IO_MASK;
				sbdev->option_reg_addr = pcidev->resource[2].start & PCI_BASE_ADDRESS_IO_MASK;
			}

			/* SB16C1053APCI */
			if (sbdev->revision == 0xc0)
			{
				int prev_port_addr = 0;

				pci_read_config_dword(pcidev, PCI_BASE_ADDRESS_0, &prev_port_addr);
				pci_remap_base(pcidev, PCI_BASE_ADDRESS_1, prev_port_addr + 8, 8);
				pci_remap_base(pcidev, PCI_BASE_ADDRESS_2, prev_port_addr + 16, 8);
				pci_remap_base(pcidev, PCI_BASE_ADDRESS_3, prev_port_addr + 24, 8);
			}
			break;
		case PCI_DEVICE_ID_MP6 :
		case PCI_DEVICE_ID_MP6A :
		case PCI_DEVICE_ID_GT_MP6 :
		case PCI_DEVICE_ID_GT_MP6A :
			sbdev->nr_ports = 6;

			/* SB16C1053APCI */
			if (sbdev->revision == 0xc0)
			{
				int prev_port_addr = 0;

				pci_read_config_dword(pcidev, PCI_BASE_ADDRESS_0, &prev_port_addr);
				pci_remap_base(pcidev, PCI_BASE_ADDRESS_1, prev_port_addr + 8, 8);
				pci_remap_base(pcidev, PCI_BASE_ADDRESS_2, prev_port_addr + 16, 16);
				pci_remap_base(pcidev, PCI_BASE_ADDRESS_3, prev_port_addr + 32, 16);
			}
			break;
		case PCI_DEVICE_ID_MP8 :
		case PCIE_DEVICE_ID_MP8 :
		case PCI_DEVICE_ID_GT_MP8 :
		case PCIE_DEVICE_ID_GT_MP8 :
		case PCIE_DEVICE_ID_MP8B :
			sbdev->nr_ports = 8;
			break;
		case PCI_DEVICE_ID_MP32 :
		case PCIE_DEVICE_ID_MP32 :
		case PCI_DEVICE_ID_GT_MP32 :
		case PCIE_DEVICE_ID_GT_MP32 :
			{
				int portnum_hex=0;
				portnum_hex = inb(sbdev->option_reg_addr);
				sbdev->nr_ports = ((portnum_hex/16)*10) + (portnum_hex % 16);
			}
			break;
#ifdef CONFIG_PARPORT_PC
		case PCI_DEVICE_ID_MP2S1P :
			sbdev->nr_ports = 2;

			/* SB16C1053APCI */
			if (sbdev->revision == 0xc0)
			{
				int prev_port_addr = 0;

				pci_read_config_dword(pcidev, PCI_BASE_ADDRESS_0, &prev_port_addr);
				pci_remap_base(pcidev, PCI_BASE_ADDRESS_1, prev_port_addr + 8, 8);
			}

			/* add PC compatible parallel port */
			parport_pc_probe_port(pcidev->resource[2].start, pcidev->resource[3].start, PARPORT_IRQ_NONE, PARPORT_DMA_NONE, &pcidev->dev, 0);
			break;
		case PCI_DEVICE_ID_MP1P :
			/* add PC compatible parallel port */
			parport_pc_probe_port(pcidev->resource[2].start, pcidev->resource[3].start, PARPORT_IRQ_NONE, PARPORT_DMA_NONE, &pcidev->dev, 0);
			break;
#endif
	}
