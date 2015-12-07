#if defined _MSC_VER || defined __MINGW32__
if((entry.length = _snprintf(tag, sizeof(tag), "%s=0x%04X", CHANNEL_MASK_TAG, (unsigned)channel_mask)) >= sizeof(tag))
#else
	if((entry.length = snprintf(tag, sizeof(tag), "%s=0x%04X", CHANNEL_MASK_TAG, (unsigned)channel_mask)) >= sizeof(tag))
#endif
		return false;
