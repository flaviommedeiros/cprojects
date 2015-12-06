if (s->s3->tmp.use_rsa_tmp
			/* PSK: send ServerKeyExchange if either:
			 *   - PSK identity hint is provided, or
			 *   - the key exchange is kEECDH.
			 */
#ifndef OPENSSL_NO_PSK
			    || ((alg_a & SSL_aPSK) && ((alg_k & SSL_kEECDH) || s->session->psk_identity_hint))
#endif
#ifndef OPENSSL_NO_SRP
			    /* SRP: send ServerKeyExchange */
			    || (alg_k & SSL_kSRP)
#endif
			    || (alg_k & (SSL_kDHr|SSL_kDHd|SSL_kEDH))
			    || (alg_k & SSL_kEECDH)
			    || ((alg_k & SSL_kRSA)
				&& (s->cert->pkeys[SSL_PKEY_RSA_ENC].privatekey == NULL
				    || (SSL_C_IS_EXPORT(s->s3->tmp.new_cipher)
					&& EVP_PKEY_size(s->cert->pkeys[SSL_PKEY_RSA_ENC].privatekey)*8 > SSL_C_EXPORT_PKEYLENGTH(s->s3->tmp.new_cipher)
					)
				    )
				)
			    )
				{
				ret=ssl3_send_server_key_exchange(s);
				if (ret <= 0) goto end;
				}
			else
				skip=1;
