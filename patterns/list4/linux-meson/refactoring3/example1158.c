switch (port->uart.line) {
#ifdef CONFIG_MN10300_TTYSM0
	case 0: /* ttySM0 */
#if   defined(CONFIG_MN10300_TTYSM0_TIMER8)
		scxctr |= SC0CTR_CK_TM8UFLOW_8;
#elif defined(CONFIG_MN10300_TTYSM0_TIMER0)
		scxctr |= SC0CTR_CK_TM0UFLOW_8;
#elif defined(CONFIG_MN10300_TTYSM0_TIMER2)
		scxctr |= SC0CTR_CK_TM2UFLOW_8;
#else
#error "Unknown config for ttySM0"
#endif
		break;
#endif /* CONFIG_MN10300_TTYSM0 */

#ifdef CONFIG_MN10300_TTYSM1
	case 1: /* ttySM1 */
#if defined(CONFIG_AM33_2) || defined(CONFIG_AM33_3)
#if   defined(CONFIG_MN10300_TTYSM1_TIMER9)
		scxctr |= SC1CTR_CK_TM9UFLOW_8;
#elif defined(CONFIG_MN10300_TTYSM1_TIMER3)
		scxctr |= SC1CTR_CK_TM3UFLOW_8;
#else
#error "Unknown config for ttySM1"
#endif
#else /* CONFIG_AM33_2 || CONFIG_AM33_3 */
#if defined(CONFIG_MN10300_TTYSM1_TIMER12)
		scxctr |= SC1CTR_CK_TM12UFLOW_8;
#else
#error "Unknown config for ttySM1"
#endif
#endif /* CONFIG_AM33_2 || CONFIG_AM33_3 */
		break;
#endif /* CONFIG_MN10300_TTYSM1 */

#ifdef CONFIG_MN10300_TTYSM2
	case 2: /* ttySM2 */
#if defined(CONFIG_AM33_2)
#if   defined(CONFIG_MN10300_TTYSM2_TIMER10)
		scxctr |= SC2CTR_CK_TM10UFLOW;
#else
#error "Unknown config for ttySM2"
#endif
#else /* CONFIG_AM33_2 */
#if   defined(CONFIG_MN10300_TTYSM2_TIMER9)
		scxctr |= SC2CTR_CK_TM9UFLOW_8;
#elif defined(CONFIG_MN10300_TTYSM2_TIMER1)
		scxctr |= SC2CTR_CK_TM1UFLOW_8;
#elif defined(CONFIG_MN10300_TTYSM2_TIMER3)
		scxctr |= SC2CTR_CK_TM3UFLOW_8;
#else
#error "Unknown config for ttySM2"
#endif
#endif /* CONFIG_AM33_2 */
		break;
#endif /* CONFIG_MN10300_TTYSM2 */

	default:
		break;
	}
