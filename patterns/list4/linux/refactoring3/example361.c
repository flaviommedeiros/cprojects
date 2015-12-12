switch (nfc->alt_buf) {
	case ALT_BUF_ID:
		tmp = vf610_nfc_get_id(nfc, c);
		break;
	case ALT_BUF_STAT:
		tmp = vf610_nfc_get_status(nfc);
		break;
#ifdef __LITTLE_ENDIAN
	case ALT_BUF_ONFI:
		/* Reverse byte since the controller uses big endianness */
		c = nfc->buf_offset ^ 0x3;
		/* fall-through */
#endif
	default:
		tmp = *((u8 *)(nfc->regs + NFC_MAIN_AREA(0) + c));
		break;
	}
