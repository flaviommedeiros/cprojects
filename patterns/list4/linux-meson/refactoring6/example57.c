if (param->u.crypt.idx >= WEP_KEYS
#ifdef CONFIG_IEEE80211W
			&& param->u.crypt.idx > BIP_MAX_KEYID
#endif //CONFIG_IEEE80211W
		)
		{
			ret = -EINVAL;
			goto exit;
		}
