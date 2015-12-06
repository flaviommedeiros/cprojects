#ifdef WITH_TLS
if (tls && (home->proto == IPPROTO_TCP)) {
			home->secret = "radsec";
		} else
#endif
		{
			cf_log_err_cs(cs, "No shared secret defined for home server %s", home->log_name);
			goto error;
		}
