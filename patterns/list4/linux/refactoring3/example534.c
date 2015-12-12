switch (get_ins_reg_width(ins_addr)) {
	case 1:
		return *(unsigned char *)p;

	case 2:
		return *(unsigned short *)p;

	case 4:
		return *(unsigned int *)p;

#ifdef __amd64__
	case 8:
		return *(unsigned long *)p;
#endif

	default:
		printk(KERN_ERR "mmiotrace: Error: width.\n");
	}
