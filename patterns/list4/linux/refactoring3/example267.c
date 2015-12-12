switch (asc_dvc_varp->bus_type) {
#ifdef CONFIG_ISA
		case ASC_IS_ISA:
			shost->unchecked_isa_dma = true;
			share_irq = 0;
			break;
		case ASC_IS_VL:
			shost->unchecked_isa_dma = false;
			share_irq = 0;
			break;
		case ASC_IS_EISA:
			shost->unchecked_isa_dma = false;
			share_irq = IRQF_SHARED;
			break;
#endif /* CONFIG_ISA */
#ifdef CONFIG_PCI
		case ASC_IS_PCI:
			shost->unchecked_isa_dma = false;
			share_irq = IRQF_SHARED;
			break;
#endif /* CONFIG_PCI */
		default:
			shost_printk(KERN_ERR, shost, "unknown adapter type: "
					"%d\n", asc_dvc_varp->bus_type);
			shost->unchecked_isa_dma = false;
			share_irq = 0;
			break;
		}
