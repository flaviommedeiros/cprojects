switch (keytype)
	{
#ifndef OPENSSL_NO_RSA
	case 1: /*RSA*/
		/* set private external reference */
		rsatmp = RSA_new_method(e);
		RSA_set_ex_data(rsatmp,rsaHndidx,hptr);
		rsatmp->flags |= RSA_FLAG_EXT_PKEY;

		/* set public big nums*/
		rsatmp->e = BN_new();
		rsatmp->n = BN_new();
		bn_expand2(rsatmp->e, el/sizeof(BN_ULONG));
		bn_expand2(rsatmp->n, el/sizeof(BN_ULONG));
		if (!rsatmp->e || rsatmp->e->dmax!=(int)(el/sizeof(BN_ULONG))|| 
			!rsatmp->n || rsatmp->n->dmax!=(int)(el/sizeof(BN_ULONG)))
			goto err;
		ret=p_surewarehk_Load_Rsa_Pubkey(msg,key_id,el,
						 (unsigned long *)rsatmp->n->d,
						 (unsigned long *)rsatmp->e->d);
		surewarehk_error_handling(msg,SUREWARE_F_SUREWARE_LOAD_PUBLIC,ret);
		if (ret!=1)
		{
			SUREWAREerr(SUREWARE_F_SUREWARE_LOAD_PUBLIC,ENGINE_R_FAILED_LOADING_PUBLIC_KEY);
			goto err;
		}
		/* normalise pub e and pub n */
		rsatmp->e->top=el/sizeof(BN_ULONG);
		bn_fix_top(rsatmp->e);
		rsatmp->n->top=el/sizeof(BN_ULONG);
		bn_fix_top(rsatmp->n);
		/* create an EVP object: engine + rsa key */
		res = EVP_PKEY_new();
		EVP_PKEY_assign_RSA(res, rsatmp);
		break;
#endif

#ifndef OPENSSL_NO_DSA
	case 2:/*DSA*/
		/* set private/public external reference */
		dsatmp = DSA_new_method(e);
		DSA_set_ex_data(dsatmp,dsaHndidx,hptr);
		/*dsatmp->flags |= DSA_FLAG_EXT_PKEY;*/

		/* set public key*/
		dsatmp->pub_key = BN_new();
		dsatmp->p = BN_new();
		dsatmp->q = BN_new();
		dsatmp->g = BN_new();
		bn_expand2(dsatmp->pub_key, el/sizeof(BN_ULONG));
		bn_expand2(dsatmp->p, el/sizeof(BN_ULONG));
		bn_expand2(dsatmp->q, 20/sizeof(BN_ULONG));
		bn_expand2(dsatmp->g, el/sizeof(BN_ULONG));
		if (!dsatmp->pub_key || dsatmp->pub_key->dmax!=(int)(el/sizeof(BN_ULONG))|| 
			!dsatmp->p || dsatmp->p->dmax!=(int)(el/sizeof(BN_ULONG)) ||
			!dsatmp->q || dsatmp->q->dmax!=20/sizeof(BN_ULONG) ||
			!dsatmp->g || dsatmp->g->dmax!=(int)(el/sizeof(BN_ULONG)))
			goto err;

		ret=p_surewarehk_Load_Dsa_Pubkey(msg,key_id,el,
						 (unsigned long *)dsatmp->pub_key->d, 
						 (unsigned long *)dsatmp->p->d,
						 (unsigned long *)dsatmp->q->d,
						 (unsigned long *)dsatmp->g->d);
		surewarehk_error_handling(msg,SUREWARE_F_SUREWARE_LOAD_PUBLIC,ret);
		if (ret!=1)
		{
			SUREWAREerr(SUREWARE_F_SUREWARE_LOAD_PUBLIC,ENGINE_R_FAILED_LOADING_PUBLIC_KEY);
			goto err;
		}
		/* set parameters */
		/* normalise pubkey and parameters in case of */
		dsatmp->pub_key->top=el/sizeof(BN_ULONG);
		bn_fix_top(dsatmp->pub_key);
		dsatmp->p->top=el/sizeof(BN_ULONG);
		bn_fix_top(dsatmp->p);
		dsatmp->q->top=20/sizeof(BN_ULONG);
		bn_fix_top(dsatmp->q);
		dsatmp->g->top=el/sizeof(BN_ULONG);
		bn_fix_top(dsatmp->g);

		/* create an EVP object: engine + rsa key */
		res = EVP_PKEY_new();
		EVP_PKEY_assign_DSA(res, dsatmp);
		break;
#endif

	default:
		SUREWAREerr(SUREWARE_F_SUREWARE_LOAD_PUBLIC,ENGINE_R_FAILED_LOADING_PRIVATE_KEY);
		goto err;
	}
