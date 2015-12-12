switch (LOBYTE(wMessage)) {
#ifndef MSND_CLASSIC
		case HIDSP_PLAY_UNDER:
#endif
		case HIDSP_INT_PLAY_UNDER:
			snd_printd(KERN_WARNING LOGNAME ": Play underflow %i\n",
				chip->banksPlayed);
			if (chip->banksPlayed > 2)
				clear_bit(F_WRITING, &chip->flags);
			break;

		case HIDSP_INT_RECORD_OVER:
			snd_printd(KERN_WARNING LOGNAME ": Record overflow\n");
			clear_bit(F_READING, &chip->flags);
			break;

		default:
			snd_printd(KERN_WARNING LOGNAME
				   ": DSP message %d 0x%02x\n",
				   LOBYTE(wMessage), LOBYTE(wMessage));
			break;
		}
