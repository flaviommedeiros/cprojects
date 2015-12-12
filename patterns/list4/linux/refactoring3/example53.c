switch (opt) {
		case 'p': save_sig = true; break;
		case 'd': sign_only = true; save_sig = true; break;
#ifndef USE_PKCS7
		case 'k': use_keyid = CMS_USE_KEYID; break;
#endif
		case -1: break;
		default: format();
		}
