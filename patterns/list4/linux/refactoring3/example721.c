switch (priv->key) {
#ifdef CONFIG_NF_CONNTRACK_MARK
	case NFT_CT_MARK:
		len = FIELD_SIZEOF(struct nf_conn, mark);
		break;
#endif
	default:
		return -EOPNOTSUPP;
	}
