switch (match_token(value, cifs_smb_version_tokens, args)) {
	case Smb_1:
		vol->ops = &smb1_operations;
		vol->vals = &smb1_values;
		break;
#ifdef CONFIG_CIFS_SMB2
	case Smb_20:
		vol->ops = &smb20_operations;
		vol->vals = &smb20_values;
		break;
	case Smb_21:
		vol->ops = &smb21_operations;
		vol->vals = &smb21_values;
		break;
	case Smb_30:
		vol->ops = &smb30_operations;
		vol->vals = &smb30_values;
		break;
	case Smb_302:
		vol->ops = &smb30_operations; /* currently identical with 3.0 */
		vol->vals = &smb302_values;
		break;
#ifdef CONFIG_CIFS_SMB311
	case Smb_311:
		vol->ops = &smb311_operations;
		vol->vals = &smb311_values;
		break;
#endif /* SMB311 */
#endif
	default:
		cifs_dbg(VFS, "Unknown vers= option specified: %s\n", value);
		return 1;
	}
