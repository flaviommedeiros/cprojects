if ((info->online < 2)
#ifdef CONFIG_ISDN_AUDIO
	    && (!(info->vonline & 1))
#endif
		) {
		/* If Modem not listening, drop data */
		kfree_skb(skb);
		return 1;
	}
