switch(codes[i].params) {
				case PARAM_COUNT:
				case PARAM_GPU:
				case PARAM_PGA:
				case PARAM_CPU:
				case PARAM_PID:
					sprintf(buf, codes[i].description, paramid);
					break;
				case PARAM_POOL:
					sprintf(buf, codes[i].description, paramid, pools[paramid]->rpc_url);
					break;
#ifdef USE_OPENCL
				case PARAM_GPUMAX:
					sprintf(buf, codes[i].description, paramid, nDevs - 1);
					break;
#endif
#ifdef HAVE_AN_FPGA
				case PARAM_PGAMAX:
					pga = numpgas();
					sprintf(buf, codes[i].description, paramid, pga - 1);
					break;
#endif
#ifdef USE_CPUMINING
				case PARAM_CPUMAX:
					if (opt_n_threads > 0)
						cpu = num_processors;
					else
						cpu = 0;
					sprintf(buf, codes[i].description, paramid, cpu - 1);
					break;
#endif
				case PARAM_PMAX:
					sprintf(buf, codes[i].description, total_pools);
					break;
				case PARAM_POOLMAX:
					sprintf(buf, codes[i].description, paramid, total_pools - 1);
					break;
				case PARAM_DMAX:
					pga = numpgas();

					sprintf(buf, codes[i].description
						, pga
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
