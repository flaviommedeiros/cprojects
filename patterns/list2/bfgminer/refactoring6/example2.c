if (
#ifdef NEED_BFG_LOWL_VCOM
					(info->lowl == &lowl_vcom && !strcasecmp(dname, "all")) ||
#endif
					_probe_device_match(info, (dname[0] == '@') ? &dname[1] : dname))
				{
					bool dont_rescan = false;
					BFG_FOREACH_DRIVER_BY_PRIORITY(dreg)
					{
						const struct device_drv * const drv = dreg->drv;
						if (!drv_algo_check(drv))
							continue;
						if (drv->lowl_probe_by_name_only)
							continue;
						if (!drv->lowl_probe)
							continue;
						if (_probe_device_do_probe(drv, info, NULL))
							return NULL;
						if (bfg_probe_result_flags & BPR_DONT_RESCAN)
							dont_rescan = true;
					}
					if (opt_hotplug && !dont_rescan)
						request_rescan = true;
					break;
				}
