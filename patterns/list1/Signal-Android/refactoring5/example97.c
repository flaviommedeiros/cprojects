#  ifdef PMULL_CAPABLE
if (PMULL_CAPABLE) {
		gcm_init_v8(ctx->Htable,ctx->H.u);
		ctx->gmult = gcm_gmult_v8;
		ctx->ghash = gcm_ghash_v8;
	} else
#  endif
#  ifdef NEON_CAPABLE
	if (NEON_CAPABLE) {
		gcm_init_neon(ctx->Htable,ctx->H.u);
		ctx->gmult = gcm_gmult_neon;
		ctx->ghash = gcm_ghash_neon;
	} else
#  endif
	{
		gcm_init_4bit(ctx->Htable,ctx->H.u);
		ctx->gmult = gcm_gmult_4bit;
		ctx->ghash = gcm_ghash_4bit;
	}
