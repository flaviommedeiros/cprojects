switch (variant) {
#ifdef JEMALLOC_BIG_ENDIAN
	case hash_variant_x86_32: expected = 0x6213303eU; break;
	case hash_variant_x86_128: expected = 0x266820caU; break;
	case hash_variant_x64_128: expected = 0xcc622b6fU; break;
#else
	case hash_variant_x86_32: expected = 0xb0f57ee3U; break;
	case hash_variant_x86_128: expected = 0xb3ece62aU; break;
	case hash_variant_x64_128: expected = 0x6384ba69U; break;
#endif
	default: not_reached();
	}
