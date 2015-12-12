switch (op->cmd) {
		case XEN_PCI_OP_conf_read:
			op->err = xen_pcibk_config_read(dev,
				  op->offset, op->size, &op->value);
			break;
		case XEN_PCI_OP_conf_write:
			op->err = xen_pcibk_config_write(dev,
				  op->offset, op->size,	op->value);
			break;
#ifdef CONFIG_PCI_MSI
		case XEN_PCI_OP_enable_msi:
			op->err = xen_pcibk_enable_msi(pdev, dev, op);
			break;
		case XEN_PCI_OP_disable_msi:
			op->err = xen_pcibk_disable_msi(pdev, dev, op);
			break;
		case XEN_PCI_OP_enable_msix:
			op->err = xen_pcibk_enable_msix(pdev, dev, op);
			break;
		case XEN_PCI_OP_disable_msix:
			op->err = xen_pcibk_disable_msix(pdev, dev, op);
			break;
#endif
		default:
			op->err = XEN_PCI_ERR_not_implemented;
			break;
		}
