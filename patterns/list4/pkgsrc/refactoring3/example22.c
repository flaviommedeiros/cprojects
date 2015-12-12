switch (data_addr.su_family) {
		case AF_INET:
			if (epsv4 && !epsv4bad) {
				pasvcmd = "EPSV";
				overbose = verbose;
				if (ftp_debug == 0)
					verbose = -1;
				result = command("EPSV");
				verbose = overbose;
				if (verbose > 0 &&
				    (result == COMPLETE || !connected))
					fprintf(ttyout, "%s\n", reply_string);
				if (!connected)
					return (1);
				/*
				 * this code is to be friendly with broken
				 * BSDI ftpd
				 */
				if (code / 10 == 22 && code != 229) {
					fputs(
"wrong server: return code must be 229\n",
						ttyout);
					result = COMPLETE + 1;
				}
				if (result != COMPLETE) {
					epsv4bad = 1;
					DPRINTF("disabling epsv4 for this "
					    "connection\n");
				}
			}
			if (result != COMPLETE) {
				pasvcmd = "PASV";
				result = command("PASV");
				if (!connected)
					return (1);
			}
			break;
#ifdef INET6
		case AF_INET6:
			if (epsv6 && !epsv6bad) {
				pasvcmd = "EPSV";
				overbose = verbose;
				if (ftp_debug == 0)
					verbose = -1;
				result = command("EPSV");
				verbose = overbose;
				if (verbose > 0 &&
				    (result == COMPLETE || !connected))
					fprintf(ttyout, "%s\n", reply_string);
				if (!connected)
					return (1);
				/*
				 * this code is to be friendly with
				 * broken BSDI ftpd
				 */
				if (code / 10 == 22 && code != 229) {
					fputs(
						"wrong server: return code must be 229\n",
						ttyout);
					result = COMPLETE + 1;
				}
				if (result != COMPLETE) {
					epsv6bad = 1;
					DPRINTF("disabling epsv6 for this "
					    "connection\n");
				}
			}
			if (result != COMPLETE) {
				pasvcmd = "LPSV";
				result = command("LPSV");
			}
			if (!connected)
				return (1);
			break;
#endif
		default:
			result = COMPLETE + 1;
			break;
		}
