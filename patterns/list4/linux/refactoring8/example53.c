static struct rng_alg rng_algs[] = { {
	.generate		= cprng_get_random,
	.seed			= cprng_reset,
	.seedsize		= DEFAULT_PRNG_KSZ + 2 * DEFAULT_BLK_SZ,
	.base			=	{
		.cra_name		= "stdrng",
		.cra_driver_name	= "ansi_cprng",
		.cra_priority		= 100,
		.cra_ctxsize		= sizeof(struct prng_context),
		.cra_module		= THIS_MODULE,
		.cra_init		= cprng_init,
		.cra_exit		= cprng_exit,
	}
#ifdef CONFIG_CRYPTO_FIPS
}, {
	.generate		= fips_cprng_get_random,
	.seed			= fips_cprng_reset,
	.seedsize		= DEFAULT_PRNG_KSZ + 2 * DEFAULT_BLK_SZ,
	.base			=	{
		.cra_name		= "fips(ansi_cprng)",
		.cra_driver_name	= "fips_ansi_cprng",
		.cra_priority		= 300,
		.cra_ctxsize		= sizeof(struct prng_context),
		.cra_module		= THIS_MODULE,
		.cra_init		= cprng_init,
		.cra_exit		= cprng_exit,
	}
#endif
} };
