if(!(p1 = (HWCryptoHook_Init_t *)
			DSO_bind_func(hwcrhk_dso, n_hwcrhk_Init)) ||
		!(p2 = (HWCryptoHook_Finish_t *)
			DSO_bind_func(hwcrhk_dso, n_hwcrhk_Finish)) ||
		!(p3 = (HWCryptoHook_ModExp_t *)
			DSO_bind_func(hwcrhk_dso, n_hwcrhk_ModExp)) ||
#ifndef OPENSSL_NO_RSA
		!(p4 = (HWCryptoHook_RSA_t *)
			DSO_bind_func(hwcrhk_dso, n_hwcrhk_RSA)) ||
		!(p5 = (HWCryptoHook_RSALoadKey_t *)
			DSO_bind_func(hwcrhk_dso, n_hwcrhk_RSALoadKey)) ||
		!(p6 = (HWCryptoHook_RSAGetPublicKey_t *)
			DSO_bind_func(hwcrhk_dso, n_hwcrhk_RSAGetPublicKey)) ||
		!(p7 = (HWCryptoHook_RSAUnloadKey_t *)
			DSO_bind_func(hwcrhk_dso, n_hwcrhk_RSAUnloadKey)) ||
#endif
		!(p8 = (HWCryptoHook_RandomBytes_t *)
			DSO_bind_func(hwcrhk_dso, n_hwcrhk_RandomBytes)) ||
		!(p9 = (HWCryptoHook_ModExpCRT_t *)
			DSO_bind_func(hwcrhk_dso, n_hwcrhk_ModExpCRT)))
		{
		HWCRHKerr(HWCRHK_F_HWCRHK_INIT,HWCRHK_R_DSO_FAILURE);
		goto err;
		}
