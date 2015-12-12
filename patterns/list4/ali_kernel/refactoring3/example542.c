switch (bank->method) {
#ifdef CONFIG_ARCH_OMAP1
	case METHOD_MPUIO:
		reg += OMAP_MPUIO_GPIO_MASKIT;
		mask = 0xffff;
		inv = 1;
		break;
#endif
#ifdef CONFIG_ARCH_OMAP15XX
	case METHOD_GPIO_1510:
		reg += OMAP1510_GPIO_INT_MASK;
		mask = 0xffff;
		inv = 1;
		break;
#endif
#ifdef CONFIG_ARCH_OMAP16XX
	case METHOD_GPIO_1610:
		reg += OMAP1610_GPIO_IRQENABLE1;
		mask = 0xffff;
		break;
#endif
#ifdef CONFIG_ARCH_OMAP730
	case METHOD_GPIO_730:
		reg += OMAP730_GPIO_INT_MASK;
		mask = 0xffffffff;
		inv = 1;
		break;
#endif
#ifdef CONFIG_ARCH_OMAP850
	case METHOD_GPIO_850:
		reg += OMAP850_GPIO_INT_MASK;
		mask = 0xffffffff;
		inv = 1;
		break;
#endif
#if defined(CONFIG_ARCH_OMAP24XX) || defined(CONFIG_ARCH_OMAP34XX)
	case METHOD_GPIO_24XX:
		reg += OMAP24XX_GPIO_IRQENABLE1;
		mask = 0xffffffff;
		break;
#endif
#if defined(CONFIG_ARCH_OMAP4)
	case METHOD_GPIO_24XX:
		reg += OMAP4_GPIO_IRQSTATUSSET0;
		mask = 0xffffffff;
		break;
#endif
	default:
		WARN_ON(1);
		return 0;
	}
