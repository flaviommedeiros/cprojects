void ieee80211_get_tkip_key(struct ieee80211_key_conf *keyconf,
			struct sk_buff *skb, enum ieee80211_tkip_key_type type,
			u8 *outkey)
{
	struct ieee80211_key *key = (struct ieee80211_key *)
			container_of(keyconf, struct ieee80211_key, conf);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	u8 *data;
	const u8 *tk;
	struct tkip_ctx *ctx;
	u16 iv16;
	u32 iv32;

	data = (u8 *)hdr + ieee80211_hdrlen(hdr->frame_control);
	iv16 = data[2] | (data[0] << 8);
	iv32 = get_unaligned_le32(&data[4]);

	tk = &key->conf.key[NL80211_TKIP_DATA_OFFSET_ENCR_KEY];
	ctx = &key->u.tkip.tx;

#ifdef CONFIG_MAC80211_TKIP_DEBUG
	printk(KERN_DEBUG "TKIP encrypt: iv16 = 0x%04x, iv32 = 0x%08x\n",
			iv16, iv32);

	if (iv32 != ctx->iv32) {
		printk(KERN_DEBUG "skb: iv32 = 0x%08x key: iv32 = 0x%08x\n",
			iv32, ctx->iv32);
		printk(KERN_DEBUG "Wrap around of iv16 in the middle of a "
			"fragmented packet\n");
	}
#endif

	/* Update the p1k only when the iv16 in the packet wraps around, this
	 * might occur after the wrap around of iv16 in the key in case of
	 * fragmented packets. */
	if (iv16 == 0 || !ctx->initialized)
		tkip_mixing_phase1(tk, ctx, hdr->addr2, iv32);

	if (type == IEEE80211_TKIP_P1_KEY) {
		memcpy(outkey, ctx->p1k, sizeof(u16) * 5);
		return;
	}

	tkip_mixing_phase2(tk, ctx, iv16, outkey);
}
