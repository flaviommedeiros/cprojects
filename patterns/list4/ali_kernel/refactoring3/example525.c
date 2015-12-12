switch (bank->method) {
#ifdef CONFIG_ARCH_OMAP1
	case METHOD_MPUIO:
		reg += OMAP_MPUIO_OUTPUT;
		break;
#endif
#ifdef CONFIG_ARCH_OMAP15XX
	case METHOD_GPIO_1510:
		reg += OMAP1510_GPIO_DATA_OUTPUT;
		break;
#endif
#ifdef CONFIG_ARCH_OMAP16XX
	case METHOD_GPIO_1610:
		reg += OMAP1610_GPIO_DATAOUT;
		break;
#endif
#ifdef CONFIG_ARCH_OMAP730
	case METHOD_GPIO_730:
		reg += OMAP730_GPIO_DATA_OUTPUT;
		break;
#endif
#ifdef CONFIG_ARCH_OMAP850
	case METHOD_GPIO_850:
		reg += OMAP850_GPIO_DATA_OUTPUT;
		break;
#endif
#if defined(CONFIG_ARCH_OMAP24XX) || defined(CONFIG_ARCH_OMAP34XX) || \
		defined(CONFIG_ARCH_OMAP4)
	case METHOD_GPIO_24XX:
		reg += OMAP24XX_GPIO_DATAOUT;
		break;
#endif
	default:
		return -EINVAL;
	}
