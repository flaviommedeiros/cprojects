static struct crypto_alg rng_algs[] = { {
	.cra_name		= "stdrng",
	.cra_driver_name	= "ansi_cprng",
	.cra_priority		= 100,
	.cra_flags		= CRYPTO_ALG_TYPE_RNG,
	.cra_ctxsize		= sizeof(struct prng_context),
	.cra_type		= &crypto_rng_type,
	.cra_module		= THIS_MODULE,
	.cra_init		= cprng_init,
	.cra_exit		= cprng_exit,
	.cra_u			= {
		.rng = {
			.rng_make_random	= cprng_get_random,
			.rng_reset		= cprng_reset,
			.seedsize = DEFAULT_PRNG_KSZ + 2*DEFAULT_BLK_SZ,
		}
	}
#ifdef CONFIG_CRYPTO_FIPS
}, {
	.cra_name		= "fips(ansi_cprng)",
	.cra_driver_name	= "fips_ansi_cprng",
	.cra_priority		= 300,
	.cra_flags		= CRYPTO_ALG_TYPE_RNG,
	.cra_ctxsize		= sizeof(struct prng_context),
	.cra_type		= &crypto_rng_type,
	.cra_module		= THIS_MODULE,
	.cra_init		= cprng_init,
	.cra_exit		= cprng_exit,
	.cra_u			= {
		.rng = {
			.rng_make_random	= fips_cprng_get_random,
			.rng_reset		= fips_cprng_reset,
			.seedsize = DEFAULT_PRNG_KSZ + 2*DEFAULT_BLK_SZ,
		}
	}
#endif
} };
