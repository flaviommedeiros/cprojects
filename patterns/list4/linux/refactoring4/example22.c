#ifdef CONFIG_CPU_SW_DOMAIN_PAN
if (user_mode(regs))
			domain = DACR_UACCESS_ENABLE;
		else
			domain = *(unsigned int *)(regs + 1);
