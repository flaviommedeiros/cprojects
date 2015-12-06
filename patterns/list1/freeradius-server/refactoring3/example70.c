switch (type) {
 		case HOME_TYPE_AUTH_ACCT:
			home->dual = true;
			break;

		case HOME_TYPE_AUTH:
		case HOME_TYPE_ACCT:
			break;

#ifdef WITH_COA
 		case HOME_TYPE_COA:
			if (home->server != NULL) {
				cf_log_err_cs(cs, "Home servers of type \"coa\" cannot point to a virtual server");
				goto error;
			}
			break;
#endif

  		case HOME_TYPE_INVALID:
 			cf_log_err_cs(cs, "Invalid type \"%s\" for home server %s", home->type_str, home->log_name);
 			goto error;
 		}
