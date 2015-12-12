switch (drbg->core->flags & DRBG_TYPE_MASK) {
#ifdef CONFIG_CRYPTO_DRBG_HMAC
	case DRBG_HMAC:
		drbg->d_ops = &drbg_hmac_ops;
		break;
#endif /* CONFIG_CRYPTO_DRBG_HMAC */
#ifdef CONFIG_CRYPTO_DRBG_HASH
	case DRBG_HASH:
		drbg->d_ops = &drbg_hash_ops;
		break;
#endif /* CONFIG_CRYPTO_DRBG_HASH */
#ifdef CONFIG_CRYPTO_DRBG_CTR
	case DRBG_CTR:
		drbg->d_ops = &drbg_ctr_ops;
		break;
#endif /* CONFIG_CRYPTO_DRBG_CTR */
	default:
		ret = -EOPNOTSUPP;
		goto err;
	}
