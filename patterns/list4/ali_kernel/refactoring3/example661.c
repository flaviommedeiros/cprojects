switch (addr) {
	case IOAPIC_REG_SELECT:
		ioapic->ioregsel = data;
		break;

	case IOAPIC_REG_WINDOW:
		ioapic_write_indirect(ioapic, data);
		break;
#ifdef	CONFIG_IA64
	case IOAPIC_REG_EOI:
		__kvm_ioapic_update_eoi(ioapic, data, IOAPIC_LEVEL_TRIG);
		break;
#endif

	default:
		break;
	}