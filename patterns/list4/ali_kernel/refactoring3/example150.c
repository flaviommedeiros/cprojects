switch (lp->depca_bus) {
#ifdef CONFIG_MCA
	case DEPCA_BUS_MCA:
		printk(" (MCA slot %d)", to_mca_device(device)->slot + 1);
		break;
#endif

#ifdef CONFIG_EISA
	case DEPCA_BUS_EISA:
		printk(" (EISA slot %d)", to_eisa_device(device)->slot);
		break;
#endif

	case DEPCA_BUS_ISA:
		break;

	default:
		printk("Unknown DEPCA bus %d\n", lp->depca_bus);
		return -ENXIO;
	}
