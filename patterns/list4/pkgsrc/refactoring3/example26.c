switch (hcode) {
		case 200:
			break;
		case 206:
			if (! restart_point) {
				warnx("Not expecting partial content header");
				goto cleanup_fetch_url;
			}
			break;
		case 300:
		case 301:
		case 302:
		case 303:
		case 305:
		case 307:
			if (EMPTYSTRING(location)) {
				warnx(
				"No redirection Location provided by server");
				goto cleanup_fetch_url;
			}
			if (redirect_loop++ > 5) {
				warnx("Too many redirections requested");
				goto cleanup_fetch_url;
			}
			if (hcode == 305) {
				if (verbose)
					fprintf(ttyout, "Redirected via %s\n",
					    location);
				rval = fetch_url(url, location,
				    proxyauth, wwwauth);
			} else {
				if (verbose)
					fprintf(ttyout, "Redirected to %s\n",
					    location);
				rval = go_fetch(location);
			}
			goto cleanup_fetch_url;
#ifndef NO_AUTH
		case 401:
		case 407:
		    {
			char **authp;
			char *auser, *apass;

			if (hcode == 401) {
				authp = &wwwauth;
				auser = uuser;
				apass = pass;
			} else {
				authp = &proxyauth;
				auser = puser;
				apass = ppass;
			}
			if (verbose || *authp == NULL ||
			    auser == NULL || apass == NULL)
				fprintf(ttyout, "%s\n", message);
			if (EMPTYSTRING(auth)) {
				warnx(
			    "No authentication challenge provided by server");
				goto cleanup_fetch_url;
			}
			if (*authp != NULL) {
				char reply[10];

				fprintf(ttyout,
				    "Authorization failed. Retry (y/n)? ");
				if (get_line(stdin, reply, sizeof(reply), NULL)
				    < 0) {
					goto cleanup_fetch_url;
				}
				if (tolower((unsigned char)reply[0]) != 'y')
					goto cleanup_fetch_url;
				auser = NULL;
				apass = NULL;
			}
			if (auth_url(auth, authp, auser, apass) == 0) {
				rval = fetch_url(url, penv,
				    proxyauth, wwwauth);
				memset(*authp, 0, strlen(*authp));
				FREEPTR(*authp);
			}
			goto cleanup_fetch_url;
		    }
#endif
		default:
			if (message)
				warnx("Error retrieving file `%s'", message);
			else
				warnx("Unknown error retrieving file");
			goto cleanup_fetch_url;
		}
