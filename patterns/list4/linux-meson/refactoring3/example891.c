switch (pLtv->typ) {
				case CFG_CNF_PORT_TYPE:
				case CFG_CNF_OWN_MAC_ADDR:
				case CFG_CNF_OWN_CHANNEL:
				case CFG_CNF_OWN_SSID:
				case CFG_CNF_OWN_ATIM_WINDOW:
				case CFG_CNF_SYSTEM_SCALE:
				case CFG_CNF_MAX_DATA_LEN:
				case CFG_CNF_PM_ENABLED:
				case CFG_CNF_MCAST_RX:
				case CFG_CNF_MAX_SLEEP_DURATION:
				case CFG_CNF_HOLDOVER_DURATION:
				case CFG_CNF_OWN_NAME:
				case CFG_CNF_LOAD_BALANCING:
				case CFG_CNF_MEDIUM_DISTRIBUTION:
#ifdef WARP
				case CFG_CNF_TX_POW_LVL:
				case CFG_CNF_CONNECTION_CNTL:
				/*case CFG_PROBE_DATA_RATE: */
#endif /* HERMES25 */
#if 1 /*;? (HCF_TYPE) & HCF_TYPE_AP */
		/*;?should we restore this to allow smaller memory footprint */
				case CFG_CNF_OWN_DTIM_PERIOD:
#ifdef WARP
				case CFG_CNF_OWN_BEACON_INTERVAL:                    /* Own Beacon Interval */
#endif /* WARP */
#ifdef USE_WDS
				case CFG_CNF_WDS_ADDR1:
				case CFG_CNF_WDS_ADDR2:
				case CFG_CNF_WDS_ADDR3:
				case CFG_CNF_WDS_ADDR4:
				case CFG_CNF_WDS_ADDR5:
				case CFG_CNF_WDS_ADDR6:
#endif
				case CFG_CNF_MCAST_PM_BUF:
				case CFG_CNF_REJECT_ANY:
#endif

				case CFG_CNF_ENCRYPTION:
				case CFG_CNF_AUTHENTICATION:
#if 1 /* ;? (HCF_TYPE) & HCF_TYPE_AP */
		/* ;?should we restore this to allow smaller memory footprint */

				case CFG_CNF_EXCL_UNENCRYPTED:
				case CFG_CNF_MCAST_RATE:
				case CFG_CNF_INTRA_BSS_RELAY:
#endif

				case CFG_CNF_MICRO_WAVE:
				/* case CFG_CNF_LOAD_BALANCING: */
				/* case CFG_CNF_MEDIUM_DISTRIBUTION: */
				/* case CFG_CNF_RX_ALL_GROUP_ADDRESS: */
				/* case CFG_CNF_COUNTRY_INFO: */
				/* case CFG_COUNTRY_STRING: */
				case CFG_AP_MODE:
				case CFG_ENCRYPT_STRING:
				/* case CFG_DRIVER_ENABLE: */
				case CFG_WOLAS_ENABLE:
				case CFG_MB_INFO:
				case CFG_IFB:
					break;
				/* Deal with this dynamic MSF RID, as it's required for WPA */
				case CFG_DRIVER_ENABLE:
					if (lp->driverEnable) {
						hcf_cntl(&(lp->hcfCtx), HCF_CNTL_ENABLE | HCF_PORT_0);
						hcf_cntl(&(lp->hcfCtx), HCF_CNTL_CONNECT);
					} else {
						hcf_cntl(&(lp->hcfCtx), HCF_CNTL_DISABLE | HCF_PORT_0);
						hcf_cntl(&(lp->hcfCtx), HCF_CNTL_DISCONNECT);
					}
					break;
				default:
					wl_act_int_off(lp);
					urq->result = hcf_put_info(&(lp->hcfCtx), (LTVP) pLtv);
					wl_act_int_on(lp);
					break;
				}
