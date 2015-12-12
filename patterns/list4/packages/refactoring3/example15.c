switch (type) {
	case LIRC_HOMEBREW:
	case LIRC_IRDEO:
	case LIRC_IRDEO_REMOTE:
	case LIRC_ANIMAX:
	case LIRC_IGOR:
		/* if nothing specified, use ttyS0/com1 and irq 4 */
		io = io ? io : 0x3f8;
		irq = irq ? irq : 4;
		break;
#ifdef CONFIG_LIRC_SERIAL_NSLU2
	case LIRC_NSLU2:
		io = io ? io : IRQ_IXP4XX_UART2;
		irq = irq ? irq : (IXP4XX_UART2_BASE_VIRT + REG_OFFSET);
		iommap = iommap ? iommap : IXP4XX_UART2_BASE_PHYS;
		ioshift = ioshift ? ioshift : 2;
		break;
#endif
	default:
		return -EINVAL;
	}
