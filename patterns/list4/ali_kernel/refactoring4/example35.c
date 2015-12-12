#if((LINUX_VERSION_CODE < KERNEL_VERSION(2,6,21)) && (!OPENSUSE_SLED))
if (michael_mic(tkey->rx_tfm_michael, &tkey->key[24], tkey->rx_hdr,
				skb->data + hdr_len, skb->len - 8 - hdr_len, mic))
#else
	if (michael_mic(tkey->rx_tfm_michael, &tkey->key[24], tkey->rx_hdr,
				skb->data + hdr_len, skb->len - 8 - hdr_len, mic))
#endif
            	return -1;
