switch (mpu_irq[n]) {
	case SNDRV_AUTO_IRQ:
		dev_warn(dev, "mpu_irq not specified: using polling mode\n");
		mpu_irq[n] = -1;
		break;
	case 2:
		mpu_irq[n] = 9;
	case 9:
		config[n] |= GALAXY_CONFIG_MPUIRQ_2;
		break;
#ifdef AZT1605
	case 3:
		config[n] |= GALAXY_CONFIG_MPUIRQ_3;
		break;
#endif
	case 5:
		config[n] |= GALAXY_CONFIG_MPUIRQ_5;
		break;
	case 7:
		config[n] |= GALAXY_CONFIG_MPUIRQ_7;
		break;
#ifdef AZT2316
	case 10:
		config[n] |= GALAXY_CONFIG_MPUIRQ_10;
		break;
#endif
	default:
		dev_err(dev, "invalid MPU IRQ %d\n", mpu_irq[n]);
		return 0;
	}
