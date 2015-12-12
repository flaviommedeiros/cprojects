switch (keycode) {
	case ADB_KEY_CAPSLOCK:
		if (!restore_capslock_events) {
			/* Generate down/up events for CapsLock every time. */
			input_report_key(ahid->input, KEY_CAPSLOCK, 1);
			input_sync(ahid->input);
			input_report_key(ahid->input, KEY_CAPSLOCK, 0);
			input_sync(ahid->input);
			return;
		}
		break;
#ifdef CONFIG_PPC_PMAC
	case ADB_KEY_POWER_OLD: /* Power key on PBook 3400 needs remapping */
		switch(pmac_call_feature(PMAC_FTR_GET_MB_INFO,
			NULL, PMAC_MB_INFO_MODEL, 0)) {
		case PMAC_TYPE_COMET:
		case PMAC_TYPE_HOOPER:
		case PMAC_TYPE_KANGA:
			keycode = ADB_KEY_POWER;
		}
		break;
	case ADB_KEY_POWER:
		/* Keep track of the power key state */
		if (up_flag)
			ahid->flags &= ~FLAG_POWER_KEY_PRESSED;
		else
			ahid->flags |= FLAG_POWER_KEY_PRESSED;

		/* Fn + Command will produce a bogus "power" keycode */
		if (ahid->flags & FLAG_FN_KEY_PRESSED) {
			keycode = ADB_KEY_CMD;
			if (up_flag)
				ahid->flags &= ~FLAG_POWER_FROM_FN;
			else
				ahid->flags |= FLAG_POWER_FROM_FN;
		} else if (ahid->flags & FLAG_POWER_FROM_FN) {
			keycode = ADB_KEY_CMD;
			ahid->flags &= ~FLAG_POWER_FROM_FN;
		}
		break;
	case ADB_KEY_FN:
		/* Keep track of the Fn key state */
		if (up_flag) {
			ahid->flags &= ~FLAG_FN_KEY_PRESSED;
			/* Emulate Fn+delete = forward delete */
			if (ahid->flags & FLAG_EMU_FWDEL_DOWN) {
				ahid->flags &= ~FLAG_EMU_FWDEL_DOWN;
				keycode = ADB_KEY_FWDEL;
				break;
			}
		} else
			ahid->flags |= FLAG_FN_KEY_PRESSED;
		break;
	case ADB_KEY_DEL:
		/* Emulate Fn+delete = forward delete */
		if (ahid->flags & FLAG_FN_KEY_PRESSED) {
			keycode = ADB_KEY_FWDEL;
			if (up_flag)
				ahid->flags &= ~FLAG_EMU_FWDEL_DOWN;
			else
				ahid->flags |= FLAG_EMU_FWDEL_DOWN;
		}
		break;
#endif /* CONFIG_PPC_PMAC */
	}
