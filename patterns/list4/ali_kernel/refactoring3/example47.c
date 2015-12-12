switch (chip->hardware) {
#ifndef OPTi93X
	case OPTi9XX_HW_82C924:
	case OPTi9XX_HW_82C925:
		if (reg > 7) {
			outb(reg, chip->mc_base + 8);
			outb(chip->password, chip->mc_base + chip->pwd_reg);
			retval = inb(chip->mc_base + 9);
			break;
		}

	case OPTi9XX_HW_82C928:
	case OPTi9XX_HW_82C929:
		retval = inb(chip->mc_base + reg);
		break;
#else	/* OPTi93X */

	case OPTi9XX_HW_82C930:
	case OPTi9XX_HW_82C931:
	case OPTi9XX_HW_82C933:
		outb(reg, chip->mc_indir_index);
		outb(chip->password, chip->mc_base + chip->pwd_reg);
		retval = inb(chip->mc_indir_index + 1);
		break;
#endif	/* OPTi93X */

	default:
		snd_printk(KERN_ERR "chip %d not supported\n", chip->hardware);
	}
