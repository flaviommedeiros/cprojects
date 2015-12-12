switch (inta_irq) {
	case IRQ_PINT0:
		bank = 0;
		break;
	case IRQ_PINT2:
		bank = 2;
		break;
	case IRQ_PINT3:
		bank = 3;
		break;
	case IRQ_PINT1:
		bank = 1;
		break;
#ifdef CONFIG_BF60x
	case IRQ_PINT4:
		bank = 4;
		break;
	case IRQ_PINT5:
		bank = 5;
		break;
#endif
	default:
		return;
	}
