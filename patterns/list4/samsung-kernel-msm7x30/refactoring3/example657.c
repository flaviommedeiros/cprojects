switch(type) {
#ifdef CONFIG_PPC_DCR
	case mpic_access_dcr:
		return dcr_read(rb->dhost, reg);
#endif
	case mpic_access_mmio_be:
		return in_be32(rb->base + (reg >> 2));
	case mpic_access_mmio_le:
	default:
		return in_le32(rb->base + (reg >> 2));
	}
