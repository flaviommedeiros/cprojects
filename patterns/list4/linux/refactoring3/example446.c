switch(type) {
#ifdef CONFIG_PPC_DCR
	case mpic_access_dcr:
		dcr_write(rb->dhost, reg, value);
		break;
#endif
	case mpic_access_mmio_be:
		out_be32(rb->base + (reg >> 2), value);
		break;
	case mpic_access_mmio_le:
	default:
		out_le32(rb->base + (reg >> 2), value);
		break;
	}
