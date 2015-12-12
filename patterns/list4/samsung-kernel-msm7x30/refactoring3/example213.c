switch (card->hw.fwid) {
#ifdef CONFIG_CYCLOMX_X25
	case CFID_X25_2X:
		rc = cycx_x25_wan_init(card, conf);
		break;
#endif
	default:
		pr_err("%s: this firmware is not supported!\n", wandev->name);
		rc = -EINVAL;
	}
