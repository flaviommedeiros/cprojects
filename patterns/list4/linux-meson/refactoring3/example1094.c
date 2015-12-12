switch (reg) {
#ifdef __i386__
	case HOST_IP:
		return buf[0]->__eip;
	case HOST_SP:
		return buf[0]->__esp;
	case HOST_BP:
		return buf[0]->__ebp;
#else
	case HOST_IP:
		return buf[0]->__rip;
	case HOST_SP:
		return buf[0]->__rsp;
	case HOST_BP:
		return buf[0]->__rbp;
#endif
	default:
		printk(UM_KERN_ERR "get_thread_regs - unknown register %d\n",
		       reg);
		return 0;
	}
