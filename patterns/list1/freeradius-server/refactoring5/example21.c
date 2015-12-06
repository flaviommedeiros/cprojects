#ifdef WITH_SASL
if (sasl && sasl->mech) {
			status = rlm_ldap_sasl_interactive(inst, request, *pconn, dn, password, sasl,
							   serverctrls, clientctrls, &error, &extra);
		} else
#endif
		{
			int ret;
			struct berval cred;

			memcpy(&cred.bv_val, &password, sizeof(cred.bv_val));
			cred.bv_len = talloc_array_length(password) - 1;

			ret = ldap_sasl_bind((*pconn)->handle, dn, LDAP_SASL_SIMPLE, &cred,
					     serverctrls, clientctrls, &msgid);
			/* We got a valid message ID */
			if ((ret == 0) && (msgid >= 0)) {
				MOD_ROPTIONAL(RDEBUG2, DEBUG2, "Waiting for bind result...");
			}

			status = rlm_ldap_result(inst, *pconn, msgid, dn, NULL, &error, &extra);
		}
