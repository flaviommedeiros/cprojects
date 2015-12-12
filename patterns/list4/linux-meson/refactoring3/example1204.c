switch (irq) {
#ifdef IRQ_RTC
	case IRQ_RTC:
	wakeup |= WAKE;
	break;
#endif
#ifdef IRQ_CAN0_RX
	case IRQ_CAN0_RX:
	wakeup |= CANWE;
	break;
#endif
#ifdef IRQ_CAN1_RX
	case IRQ_CAN1_RX:
	wakeup |= CANWE;
	break;
#endif
#ifdef IRQ_USB_INT0
	case IRQ_USB_INT0:
	wakeup |= USBWE;
	break;
#endif
#ifdef CONFIG_BF54x
	case IRQ_CNT:
	wakeup |= ROTWE;
	break;
#endif
	default:
	break;
	}
