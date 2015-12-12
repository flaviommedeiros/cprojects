switch (cmd) {
	case H_ENTER:
	case H_REMOVE:
	case H_PROTECT:
	case H_BULK_REMOVE:
	case H_PUT_TCE:
	case H_CEDE:
	case H_LOGICAL_CI_LOAD:
	case H_LOGICAL_CI_STORE:
#ifdef CONFIG_KVM_XICS
	case H_XIRR:
	case H_CPPR:
	case H_EOI:
	case H_IPI:
	case H_IPOLL:
	case H_XIRR_X:
#endif
		return 1;
	}
