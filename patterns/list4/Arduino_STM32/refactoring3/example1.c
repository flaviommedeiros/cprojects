switch (dev->clk_id) {
    case RCC_TIMER2:
        nvic_irq_enable(NVIC_TIMER2);
        break;
    case RCC_TIMER3:
        nvic_irq_enable(NVIC_TIMER3);
        break;
    case RCC_TIMER4:
        nvic_irq_enable(NVIC_TIMER4);
        break;
#ifdef STM32_HIGH_DENSITY
    case RCC_TIMER5:
        nvic_irq_enable(NVIC_TIMER5);
        break;
    case RCC_TIMER6:
        nvic_irq_enable(NVIC_TIMER6);
        break;
    case RCC_TIMER7:
        nvic_irq_enable(NVIC_TIMER7);
        break;
#endif
    default:
        ASSERT_FAULT(0);
        break;
    }
