if (force_dwlan || (get_wans_dualwan() & WANSCAP_WAN)
#if defined(RTCONFIG_RALINK)
				    || (!nvram_match("switch_wantag", "none") && !nvram_match("switch_wantag", ""))
#endif
				   )
				{
					wphy = dw_lan;
				} else
					wphy = wan;
