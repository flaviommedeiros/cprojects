switch (option->type) {
		case IORESOURCE_IO:
			ret = pnp_assign_port(dev, &option->u.port, nport++);
			break;
		case IORESOURCE_MEM:
			ret = pnp_assign_mem(dev, &option->u.mem, nmem++);
			break;
		case IORESOURCE_IRQ:
			ret = pnp_assign_irq(dev, &option->u.irq, nirq++);
			break;
#ifdef CONFIG_ISA_DMA_API
		case IORESOURCE_DMA:
			ret = pnp_assign_dma(dev, &option->u.dma, ndma++);
			break;
#endif
		default:
			ret = -EINVAL;
			break;
		}
