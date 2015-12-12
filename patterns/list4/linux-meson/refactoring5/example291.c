#ifdef CONFIG_CLKSRC_SAMSUNG_PWM
if (soc_is_exynos4210() && samsung_rev() == EXYNOS4210_REV_0)
			samsung_pwm_clocksource_init(S3C_VA_TIMER,
					timer_irqs, &exynos4_pwm_variant);
		else
#endif
			mct_init(S5P_VA_SYSTIMER, EXYNOS4_IRQ_MCT_G0,
					EXYNOS4_IRQ_MCT_L0, EXYNOS4_IRQ_MCT_L1);
