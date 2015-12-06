#ifndef OPENSSL_NO_DSA
if (dsaparam)
			{
			DSA *dsa = DSA_new();
			
			BIO_printf(bio_err,"Generating DSA parameters, %d bit long prime\n",num);
			if(!dsa || !DSA_generate_parameters_ex(dsa, num,
						NULL, 0, NULL, NULL, &cb))
				{
				if(dsa) DSA_free(dsa);
				ERR_print_errors(bio_err);
				goto end;
				}

			dh = DSA_dup_DH(dsa);
			DSA_free(dsa);
			if (dh == NULL)
				{
				ERR_print_errors(bio_err);
				goto end;
				}
			}
		else
#endif
			{
			dh = DH_new();
			BIO_printf(bio_err,"Generating DH parameters, %d bit long safe prime, generator %d\n",num,g);
			BIO_printf(bio_err,"This is going to take a long time\n");
			if(!dh || !DH_generate_parameters_ex(dh, num, g, &cb))
				{
				ERR_print_errors(bio_err);
				goto end;
				}
			}
