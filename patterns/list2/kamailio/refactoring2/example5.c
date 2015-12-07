#ifdef HAVE_RESOLV_RES
if ((cfg_get(core, core_cfg, dns_search_fmatch)==0) ||
						(match_search_list(&_res, rec_name+name_len+1)!=0))
#endif
					fullname_rd=rd;
