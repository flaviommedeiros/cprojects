#if (LIBNUMA_API_VERSION > 1)
if (MY_TEST(*mask, i))
#else
		if (MY_TEST(mask, i))
#endif
			rc += (1 << i);
