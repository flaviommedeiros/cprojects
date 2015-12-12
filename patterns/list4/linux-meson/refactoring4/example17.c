#if IS_ENABLED(CONFIG_BQL)
if (!ring->q_vector || (ring->q_vector->itr < IXGBE_100K_ITR))
#else
	if (!ring->q_vector || (ring->q_vector->itr < 8))
#endif
		txdctl |= (1 << 16);	/* WTHRESH = 1 */
	else
		txdctl |= (8 << 16);
