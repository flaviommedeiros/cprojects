#  ifdef NEON_CAPABLE
if (NEON_CAPABLE) {
        gcm_init_neon(ctx->Htable, ctx->H.u);
        ctx->gmult = gcm_gmult_neon;
        ctx->ghash = gcm_ghash_neon;
    } else
#  endif
    {
        gcm_init_4bit(ctx->Htable, ctx->H.u);
        ctx->gmult = gcm_gmult_4bit;
#  if defined(GHASH)
        ctx->ghash = gcm_ghash_4bit;
#  else
        ctx->ghash = NULL;
#  endif
    }
