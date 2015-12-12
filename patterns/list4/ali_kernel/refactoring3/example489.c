switch ((ixp2000_reg_read(IXP_PRODUCT_ID) >> 8) & 0x1fff) {
#ifdef CONFIG_ARCH_IXP2000
	case 0:		/* IXP2800 */
	case 1:		/* IXP2850 */
		ixp2000_uengine_mask = 0x00ff00ff;
		break;

	case 2:		/* IXP2400 */
		ixp2000_uengine_mask = 0x000f000f;
		break;
#endif

#ifdef CONFIG_ARCH_IXP23XX
	case 4:		/* IXP23xx */
		ixp2000_uengine_mask = (*IXP23XX_EXP_CFG_FUSE >> 8) & 0xf;
		break;
#endif

	default:
		printk(KERN_INFO "Detected unknown IXP2000 model (%.8x)\n",
			(unsigned int)ixp2000_reg_read(IXP_PRODUCT_ID));
		ixp2000_uengine_mask = 0x00000000;
		break;
	}
