switch(codes[i].params) {
				case PARAM_PGA:
				case PARAM_ASC:
				case PARAM_PID:
				case PARAM_INT:
					sprintf(buf, codes[i].description, paramid);
					break;
				case PARAM_POOL:
					sprintf(buf, codes[i].description, paramid, pools[paramid]->rpc_url);
					break;
#ifdef HAVE_AN_FPGA
				case PARAM_PGAMAX:
					pga = numpgas();
					sprintf(buf, codes[i].description, paramid, pga - 1);
					break;
#endif
#ifdef HAVE_AN_ASIC
				case PARAM_ASCMAX:
					asc = numascs();
					sprintf(buf, codes[i].description, paramid, asc - 1);
					break;
#endif
				case PARAM_PMAX:
					sprintf(buf, codes[i].description, total_pools);
					break;
				case PARAM_POOLMAX:
					sprintf(buf, codes[i].description, paramid, total_pools - 1);
					break;
				case PARAM_DMAX:
#ifdef HAVE_AN_ASIC
					asc = numascs();
#endif
#ifdef HAVE_AN_FPGA
					pga = numpgas();
#endif

					sprintf(buf, codes[i].description
#ifdef HAVE_AN_ASIC
						, asc
#endif
#ifdef HAVE_AN_FPGA
						, pga
#endif
						);
					break;
				case PARAM_CMD:
					sprintf(buf, codes[i].description, JSON_COMMAND);
					break;
				case PARAM_STR:
					sprintf(buf, codes[i].description, param2);
					break;
				case PARAM_BOTH:
					sprintf(buf, codes[i].description, paramid, param2);
					break;
				case PARAM_BOOL:
					sprintf(buf, codes[i].description, paramid ? TRUESTR : FALSESTR);
					break;
				case PARAM_SET:
					sprintf(buf, codes[i].description, param2, paramid);
					break;
				case PARAM_NONE:
				default:
					strcpy(buf, codes[i].description);
			}
