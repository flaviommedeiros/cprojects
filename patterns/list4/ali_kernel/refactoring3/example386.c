switch(base_port) {
	case I8042_DATA_REG:
		if (!(np = of_find_compatible_node(NULL, NULL, "pnpPNP,303")))
			np = of_find_compatible_node(NULL, NULL, "pnpPNP,f03");
		if (np) {
			parent = of_get_parent(np);
			of_node_put(np);
			np = parent;
			break;
		}
		np = of_find_node_by_type(NULL, "8042");
		/* Pegasos has no device_type on its 8042 node, look for the
		 * name instead */
		if (!np)
			np = of_find_node_by_name(NULL, "8042");
		break;
	case FDC_BASE: /* FDC1 */
		np = of_find_node_by_type(NULL, "fdc");
		break;
#ifdef CONFIG_PPC_PREP
	case _PIDXR:
	case _PNPWRP:
	case PNPBIOS_BASE:
		/* implement me */
#endif
	default:
		/* ipmi is supposed to fail here */
		break;
	}
