switch (vp->da->attr) {
		case PW_USER_PASSWORD: /* deprecated */
			RWDEBUG("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			RWDEBUG("!!! Ignoring control:User-Password.  Update your        !!!");
			RWDEBUG("!!! configuration so that the \"known good\" clear text !!!");
			RWDEBUG("!!! password is in Cleartext-Password and NOT in        !!!");
			RWDEBUG("!!! User-Password.                                      !!!");
			RWDEBUG("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
			break;

		case PW_PASSWORD_WITH_HEADER:	/* preferred */
		{
			VALUE_PAIR *new;

			/*
			 *	Password already exists: use that instead of this one.
			 */
			if (fr_pair_find_by_num(request->config, 0, PW_CLEARTEXT_PASSWORD, TAG_ANY)) {
				RWDEBUG("Config already contains a \"known good\" password "
					"(&control:Cleartext-Password).  Ignoring &config:Password-With-Header");
				break;
			}

			new = normify_with_header(request, vp);
			if (new) fr_cursor_insert(&cursor, new); /* inserts at the end of the list */

			RDEBUG2("Removing &control:Password-With-Header");
			vp = fr_cursor_remove(&cursor);	/* advances the cursor for us */
			talloc_free(vp);

			found_pw = true;

			vp = fr_cursor_current(&cursor);
			if (vp) goto next;
		}
			break;

		case PW_CLEARTEXT_PASSWORD:
		case PW_CRYPT_PASSWORD:
		case PW_NS_MTA_MD5_PASSWORD:
			found_pw = true;
			break;	/* don't touch these */

		case PW_MD5_PASSWORD:
		case PW_SMD5_PASSWORD:
		case PW_NT_PASSWORD:
		case PW_LM_PASSWORD:
			if (inst->normify) {
				normify(request, vp, 16); /* ensure it's in the right format */
			}
			found_pw = true;
			break;

#ifdef HAVE_OPENSSL_EVP_H
		case PW_SHA2_PASSWORD:
			if (inst->normify) {
				normify(request, vp, 28); /* ensure it's in the right format */
			}
			found_pw = true;
			break;

		case PW_SSHA2_224_PASSWORD:
			if (inst->normify) {
				normify(request, vp, 28); /* ensure it's in the right format */
			}
			found_pw = true;
			break;

		case PW_SSHA2_256_PASSWORD:
			if (inst->normify) {
				normify(request, vp, 32); /* ensure it's in the right format */
			}
			found_pw = true;
			break;

		case PW_SSHA2_384_PASSWORD:
			if (inst->normify) {
				normify(request, vp, 48); /* ensure it's in the right format */
			}
			found_pw = true;
			break;

		case PW_SSHA2_512_PASSWORD:
			if (inst->normify) {
				normify(request, vp, 64); /* ensure it's in the right format */
			}
			found_pw = true;
			break;
#endif

		case PW_SHA_PASSWORD:
		case PW_SSHA_PASSWORD:
			if (inst->normify) {
				normify(request, vp, 20); /* ensure it's in the right format */
			}
			found_pw = true;
			break;

			/*
			 *	If it's proxied somewhere, don't complain
			 *	about not having passwords or Auth-Type.
			 */
		case PW_PROXY_TO_REALM:
		{
			REALM *realm = realm_find(vp->vp_strvalue);
			if (realm && realm->auth_pool) {
				return RLM_MODULE_NOOP;
			}
			break;
		}

		case PW_AUTH_TYPE:
			auth_type = true;

			/*
			 *	Auth-Type := Accept
			 *	Auth-Type := Reject
			 */
			if ((vp->vp_integer == 254) ||
			    (vp->vp_integer == 4)) {
			    found_pw = true;
			}
			break;

		default:
			break;	/* ignore it */

		}
