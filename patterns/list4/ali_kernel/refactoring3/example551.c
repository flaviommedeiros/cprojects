switch (bank->method) {
#ifdef CONFIG_ARCH_OMAP16XX
	case METHOD_MPUIO:
	case METHOD_GPIO_1610:
		spin_lock_irqsave(&bank->lock, flags);
		if (enable)
			bank->suspend_wakeup |= (1 << gpio);
		else
			bank->suspend_wakeup &= ~(1 << gpio);
		spin_unlock_irqrestore(&bank->lock, flags);
		return 0;
#endif
#if defined(CONFIG_ARCH_OMAP24XX) || defined(CONFIG_ARCH_OMAP34XX) || \
				defined(CONFIG_ARCH_OMAP4)
	case METHOD_GPIO_24XX:
		if (bank->non_wakeup_gpios & (1 << gpio)) {
			printk(KERN_ERR "Unable to modify wakeup on "
					"non-wakeup GPIO%d\n",
					(bank - gpio_bank) * 32 + gpio);
			return -EINVAL;
		}
		spin_lock_irqsave(&bank->lock, flags);
		if (enable)
			bank->suspend_wakeup |= (1 << gpio);
		else
			bank->suspend_wakeup &= ~(1 << gpio);
		spin_unlock_irqrestore(&bank->lock, flags);
		return 0;
#endif
	default:
		printk(KERN_ERR "Can't enable GPIO wakeup for method %i\n",
		       bank->method);
		return -EINVAL;
	}
