#ifdef USE_DNS_FAILOVER
if (cfg_get(core, core_cfg, use_dns_failover)){
			dns_srv_handle_init(&dns_srv_h);
			err=dns_sip_resolve2su(&dns_srv_h, &send_info->to, dst, port,
									&proto, dns_flags);
			if (err!=0){
				LM_ERR("resolving \"%.*s\" failed: %s [%d]\n",
						dst->len, ZSW(dst->s), dns_strerror(err), err);
				ret=E_BAD_ADDRESS;
				goto error;
			}
		}else
#endif
		if (sip_hostport2su(&send_info->to, dst, port, &proto)<0){
			LM_ERR("bad host name %.*s, dropping packet\n", dst->len, ZSW(dst->s));
			ret=E_BAD_ADDRESS;
			goto error;
		}
