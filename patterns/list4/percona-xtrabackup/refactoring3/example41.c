switch (setting)
	{
		case 0: return QLZ_COMPRESSION_LEVEL;
		case 1: return sizeof(qlz_state_compress);
		case 2: return sizeof(qlz_state_decompress);
		case 3: return QLZ_STREAMING_BUFFER;
#ifdef QLZ_MEMORY_SAFE
		case 6: return 1;
#else
		case 6: return 0;
#endif
		case 7: return QLZ_VERSION_MAJOR;
		case 8: return QLZ_VERSION_MINOR;
		case 9: return QLZ_VERSION_REVISION;
	}
