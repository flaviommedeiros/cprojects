if (
#ifdef USE_DNS_FAILOVER
								uri2dst(0, &di, 0, uri, proto)
#else
								uri2dst(&di, 0, uri, proto)
#endif /* USE_DNS_FAILOVER */
									== 0 ){
							LOG(L_ERR, "ERROR: get_hfblock: send_sock"
										" failed\n");
							goto error;
						}
