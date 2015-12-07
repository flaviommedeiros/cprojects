if (!ptypes && !preauth
		    && ret == KRB5KDC_ERR_PREAUTH_REQUIRED
#if 0
			|| ret == KRB5KDC_ERR_BADOPTION
#endif
		    && set_ptypes(context, &error, &ptypes, &my_preauth)) {
		    done = 0;
		    preauth = my_preauth;
		    krb5_free_error_contents(context, &error);
		    krb5_clear_error_message(context);
		    continue;
		}
