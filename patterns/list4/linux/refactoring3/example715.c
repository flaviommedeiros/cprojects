switch (priv->key) {
	case NFT_CT_DIRECTION:
		*dest = CTINFO2DIR(ctinfo);
		return;
	case NFT_CT_STATUS:
		*dest = ct->status;
		return;
#ifdef CONFIG_NF_CONNTRACK_MARK
	case NFT_CT_MARK:
		*dest = ct->mark;
		return;
#endif
#ifdef CONFIG_NF_CONNTRACK_SECMARK
	case NFT_CT_SECMARK:
		*dest = ct->secmark;
		return;
#endif
	case NFT_CT_EXPIRATION:
		diff = (long)jiffies - (long)ct->timeout.expires;
		if (diff < 0)
			diff = 0;
		*dest = jiffies_to_msecs(diff);
		return;
	case NFT_CT_HELPER:
		if (ct->master == NULL)
			goto err;
		help = nfct_help(ct->master);
		if (help == NULL)
			goto err;
		helper = rcu_dereference(help->helper);
		if (helper == NULL)
			goto err;
		strncpy((char *)dest, helper->name, NF_CT_HELPER_NAME_LEN);
		return;
#ifdef CONFIG_NF_CONNTRACK_LABELS
	case NFT_CT_LABELS: {
		struct nf_conn_labels *labels = nf_ct_labels_find(ct);
		unsigned int size;

		if (!labels) {
			memset(dest, 0, NF_CT_LABELS_MAX_SIZE);
			return;
		}

		size = labels->words * sizeof(long);
		memcpy(dest, labels->bits, size);
		if (size < NF_CT_LABELS_MAX_SIZE)
			memset(((char *) dest) + size, 0,
			       NF_CT_LABELS_MAX_SIZE - size);
		return;
	}
#endif
	default:
		break;
	}
