switch (EncryptionMode) {
	case ZM_WEP64:
		keyLen = 5;
		break;
	case ZM_WEP128:
		keyLen = 13;
		break;
	case ZM_WEP256:
		keyLen = 29;
		break;
	case ZM_AES:
		keyLen = 16;
		break;
	case ZM_TKIP:
		keyLen = 32;
		break;
	#ifdef ZM_ENABLE_CENC
	case ZM_CENC:
		/* ZM_ENABLE_CENC */
		keyLen = 32;
		break;
	#endif
	case ZM_NO_WEP:
		keyLen = 0;
		break;
	default:
		keyLen = 0;
		printk(KERN_ERR "Unknown EncryMode\n");
		break;
	}
