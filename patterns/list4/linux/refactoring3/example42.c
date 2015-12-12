switch (LOBYTE(wMessage)) {
#ifndef MSND_CLASSIC
		case HIDSP_PLAY_UNDER:
#endif
		case HIDSP_INT_PLAY_UNDER:
/*			printk(KERN_DEBUG LOGNAME ": Play underflow\n"); */
			clear_bit(F_WRITING, &dev.flags);
			break;

		case HIDSP_INT_RECORD_OVER:
/*			printk(KERN_DEBUG LOGNAME ": Record overflow\n"); */
			clear_bit(F_READING, &dev.flags);
			break;

		default:
/*			printk(KERN_DEBUG LOGNAME ": DSP message %d 0x%02x\n",
			LOBYTE(wMessage), LOBYTE(wMessage)); */
			break;
		}
