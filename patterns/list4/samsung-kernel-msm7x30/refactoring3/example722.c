switch (ctxt->op_bytes) {
	case 2:
		ctxt->_eip = (u16)dst;
		break;
	case 4:
		ctxt->_eip = (u32)dst;
		break;
#ifdef CONFIG_X86_64
	case 8:
		if ((cs_l && is_noncanonical_address(dst)) ||
		    (!cs_l && (dst >> 32) != 0))
			return emulate_gp(ctxt, 0);
		ctxt->_eip = dst;
		break;
#endif
	default:
		WARN(1, "unsupported eip assignment size\n");
	}
