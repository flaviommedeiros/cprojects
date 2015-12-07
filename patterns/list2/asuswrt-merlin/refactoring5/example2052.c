#ifdef CONFIG_TR
if (priv->is_trdev)
		min_frame_size = LEC_MINIMUM_8025_SIZE;
	else
#endif
		min_frame_size = LEC_MINIMUM_8023_SIZE;
