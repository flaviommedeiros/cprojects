#ifdef CONFIG_ARCH_RPC
if (slot < 8) {
		ec_set_resource(ec, ECARD_RES_EASI,
				PODSLOT_EASI_BASE + (slot << 24),
				PODSLOT_EASI_SIZE);
	}
