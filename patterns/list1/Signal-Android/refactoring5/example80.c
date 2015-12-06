#ifdef VPAES_CAPABLE
if (VPAES_CAPABLE)
			{
			vpaes_set_encrypt_key(key,ctx->key_len*8,&gctx->ks.ks);
			CRYPTO_gcm128_init(&gctx->gcm,&gctx->ks,
					(block128_f)vpaes_encrypt);
			gctx->ctr = NULL;
			break;
			}
		else
#endif
		(void)0;
