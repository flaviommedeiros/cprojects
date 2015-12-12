#if((LINUX_VERSION_CODE < KERNEL_VERSION(2,6,21)) && (!OPENSUSE_SLED))
if (michael_mic(tkey->tx_tfm_michael, &tkey->key[16], tkey->tx_hdr,
				skb->data + hdr_len, skb->len - 8 - hdr_len, pos))
#else
	if (michael_mic(tkey->tx_tfm_michael, &tkey->key[16], tkey->tx_hdr,
				skb->data + hdr_len, skb->len - 8 - hdr_len, pos))
#endif
		return -1;
