switch (bank) {
	case 0:
		pint_irq = IRQ_PINT0;
		break;
	case 2:
		pint_irq = IRQ_PINT2;
		break;
	case 3:
		pint_irq = IRQ_PINT3;
		break;
	case 1:
		pint_irq = IRQ_PINT1;
		break;
#ifdef CONFIG_BF60x
	case 4:
		pint_irq = IRQ_PINT4;
		break;
	case 5:
		pint_irq = IRQ_PINT5;
		break;
#endif
	default:
		return -EINVAL;
	}
