static struct fmt_tests tests[] = {
	{"The quick brown fox jumps over the lazy dog#f7bc83f430538424b13298e6aa6fb143ef4d59a14946175997479dbc2d1a3cd8", "key"},
	{"#b613679a0814d9ec772f95d778c35fc5ff1697c493715653c6c712144292c5ad", ""},
	{"Beppe#Grillo#14651BA87C7F7DA88BCE0DF1F89C223975AC0FDF9C35378CB0857A81DFD5C408", "Io credo nella reincarnazione e sono di Genova; per cui ho fatto testamento e mi sono lasciato tutto a me."},
	{"jquYnUyWT5NsbvjQDZXyCxMJB6PryALZdYOZ1bEuagcUmYcbqpx5vOvpxj7VEhqW7OIzHR2O9JLDKrhuDfZxQk9jOENQb4OzEkRZmN8czdGdo7nshdYU1zcdoDGVb3YTCbjeZvazi#c8b4b8a7888787eebca16099fd076092269919bb032bfec48eed7f41d42eba9a", "magnum"},
#ifndef SIMD_COEF_32
	{"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234#5ad2e1646ed45675e2df32e5fcbf37d6c8830a814c4af0c166fe69a2ef1f277c","1234567890" },
	{"12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012#ff504b06ee64f3ba7fe503496b451cf46ee34109a62d55cd4bf4f38077ee8145","1234567890" },
	{"012345678901234567890123456789012345678901234567890123456789#6ec69f97e81e58b4a28ee13537c84df316cf8a6250e932de1d375e72843b8f9c", "123456"},
	{"123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123#389c4d8db62dea4c108cf12662da3c9440149800cd1e74f3738ba804024343b7","1234567890" },
	{"0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789#090487f586965594ae55d366cc9bc96d9f0ce44e253e975a1ed004c8a5edcf24", "123456"},
#endif
	{NULL}
};
