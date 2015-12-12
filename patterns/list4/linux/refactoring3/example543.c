switch (__raw_readw(PA_VERREG) & 0xf0) {
#ifdef CONFIG_RTS7751R2D_PLUS
	case 0x10:
		printk(KERN_INFO "Using R2D-PLUS interrupt controller.\n");
		d = &intc_desc_r2d_plus;
		memcpy(irl2irq, irl2irq_r2d_plus, R2D_NR_IRL);
		break;
#endif
#ifdef CONFIG_RTS7751R2D_1
	case 0x00: /* according to manual */
	case 0x30: /* in reality */
		printk(KERN_INFO "Using R2D-1 interrupt controller.\n");
		d = &intc_desc_r2d_1;
		memcpy(irl2irq, irl2irq_r2d_1, R2D_NR_IRL);
		break;
#endif
	default:
		printk(KERN_INFO "Unknown R2D interrupt controller 0x%04x\n",
		       __raw_readw(PA_VERREG));
		return;
	}
