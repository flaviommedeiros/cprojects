if (bdlp->bfl_list[i] != DLT_EN10MB
#ifdef DLT_IPNET
				    && bdlp->bfl_list[i] != DLT_IPNET
#endif
				    ) {
					is_ethernet = 0;
					break;
				}
