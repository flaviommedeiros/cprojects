switch (gdbstub_port->clock_src) {
	case MNSCx_CLOCK_SRC_IOCLK:
		gdbstub_port->ioclk = MN10300_IOCLK;
		break;

#ifdef MN10300_IOBCLK
	case MNSCx_CLOCK_SRC_IOBCLK:
		gdbstub_port->ioclk = MN10300_IOBCLK;
		break;
#endif
	default:
		BUG();
	}
