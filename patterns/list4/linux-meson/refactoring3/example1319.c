switch (match_token(value, cifs_secflavor_tokens, args)) {
	case Opt_sec_krb5:
		vol->secFlg |= CIFSSEC_MAY_KRB5 | CIFSSEC_MAY_SIGN;
		break;
	case Opt_sec_krb5i:
		vol->secFlg |= CIFSSEC_MAY_KRB5 | CIFSSEC_MUST_SIGN;
		break;
	case Opt_sec_krb5p:
		/* vol->secFlg |= CIFSSEC_MUST_SEAL | CIFSSEC_MAY_KRB5; */
		cifs_dbg(VFS, "Krb5 cifs privacy not supported\n");
		break;
	case Opt_sec_ntlmssp:
		vol->secFlg |= CIFSSEC_MAY_NTLMSSP;
		break;
	case Opt_sec_ntlmsspi:
		vol->secFlg |= CIFSSEC_MAY_NTLMSSP | CIFSSEC_MUST_SIGN;
		break;
	case Opt_ntlm:
		/* ntlm is default so can be turned off too */
		vol->secFlg |= CIFSSEC_MAY_NTLM;
		break;
	case Opt_sec_ntlmi:
		vol->secFlg |= CIFSSEC_MAY_NTLM | CIFSSEC_MUST_SIGN;
		break;
	case Opt_sec_ntlmv2:
		vol->secFlg |= CIFSSEC_MAY_NTLMV2;
		break;
	case Opt_sec_ntlmv2i:
		vol->secFlg |= CIFSSEC_MAY_NTLMV2 | CIFSSEC_MUST_SIGN;
		break;
#ifdef CONFIG_CIFS_WEAK_PW_HASH
	case Opt_sec_lanman:
		vol->secFlg |= CIFSSEC_MAY_LANMAN;
		break;
#endif
	case Opt_sec_none:
		vol->nullauth = 1;
		vol->secFlg |= CIFSSEC_MAY_NTLM;
		break;
	default:
		cifs_dbg(VFS, "bad security option: %s\n", value);
		return 1;
	}
