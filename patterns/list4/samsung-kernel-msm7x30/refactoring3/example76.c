switch (card->lan_type) {
#ifdef CONFIG_ETHERNET
	case LCS_FRAME_TYPE_ENET:
		card->lan_type_trans = eth_type_trans;
		dev = alloc_etherdev(0);
		break;
#endif
#ifdef CONFIG_TR
	case LCS_FRAME_TYPE_TR:
		card->lan_type_trans = tr_type_trans;
		dev = alloc_trdev(0);
		break;
#endif
#ifdef CONFIG_FDDI
	case LCS_FRAME_TYPE_FDDI:
		card->lan_type_trans = fddi_type_trans;
		dev = alloc_fddidev(0);
		break;
#endif
	default:
		LCS_DBF_TEXT(3, setup, "errinit");
		pr_err(" Initialization failed\n");
		goto out;
	}
