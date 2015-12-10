switch ((int) cp) {
	case DUK_ASC_BACKSLASH: break;
	case DUK_ASC_DOUBLEQUOTE: break;
	case DUK_ASC_SLASH: break;
	case DUK_ASC_LC_T: cp = 0x09; break;
	case DUK_ASC_LC_N: cp = 0x0a; break;
	case DUK_ASC_LC_R: cp = 0x0d; break;
	case DUK_ASC_LC_F: cp = 0x0c; break;
	case DUK_ASC_LC_B: cp = 0x08; break;
	case DUK_ASC_LC_U: {
		cp = duk__dec_decode_hex_escape(js_ctx, 4);
		break;
	}
#ifdef DUK_USE_JX
	case DUK_ASC_UC_U: {
		if (js_ctx->flag_ext_custom) {
			cp = duk__dec_decode_hex_escape(js_ctx, 8);
		} else {
			return 1;  /* syntax error */
		}
		break;
	}
	case DUK_ASC_LC_X: {
		if (js_ctx->flag_ext_custom) {
			cp = duk__dec_decode_hex_escape(js_ctx, 2);
		} else {
			return 1;  /* syntax error */
		}
		break;
	}
#endif  /* DUK_USE_JX */
	default:
		/* catches EOF (0x00) */
		return 1;  /* syntax error */
	}
