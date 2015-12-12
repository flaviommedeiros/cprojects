switch (data_addr.su_family) {
		case AF_INET:
			if (!epsv4 || epsv4bad) {
				result = COMPLETE + 1;
				break;
			}
			/* FALLTHROUGH */
#ifdef INET6
		case AF_INET6:
			if (!epsv6 || epsv6bad) {
				result = COMPLETE + 1;
				break;
			}
#endif
			af = (data_addr.su_family == AF_INET) ? 1 : 2;
			tmp = data_addr;
#ifdef INET6
			if (tmp.su_family == AF_INET6)
				tmp.si_su.su_sin6.sin6_scope_id = 0;
#endif
			if (getnameinfo((struct sockaddr *)&tmp.si_su,
			    tmp.su_len, hname, sizeof(hname), sname,
			    sizeof(sname), NI_NUMERICHOST | NI_NUMERICSERV)) {
				result = ERROR;
			} else {
				overbose = verbose;
				if (ftp_debug == 0)
					verbose = -1;
				result = command("EPRT |%u|%s|%s|", af, hname,
				    sname);
				verbose = overbose;
				if (verbose > 0 &&
				    (result == COMPLETE || !connected))
					fprintf(ttyout, "%s\n", reply_string);
				if (!connected)
					return (1);
				if (result != COMPLETE) {
					epsv4bad = 1;
					DPRINTF("disabling epsv4 for this "
					    "connection\n");
				}
			}
			break;
		default:
			result = COMPLETE + 1;
			break;
		}
