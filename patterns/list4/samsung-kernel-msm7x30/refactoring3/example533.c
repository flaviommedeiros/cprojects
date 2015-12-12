switch( lp->ltvRecord.typ ) {
			/* simple int gets just need the first hcf_16 byte flipped */
			case CFG_CNF_PORT_TYPE:
			case CFG_CNF_OWN_CHANNEL:
			case CFG_CNF_OWN_ATIM_WINDOW:
			case CFG_CNF_SYSTEM_SCALE:
			case CFG_CNF_MAX_DATA_LEN:
			case CFG_CNF_PM_ENABLED:
			case CFG_CNF_MCAST_RX:
			case CFG_CNF_MAX_SLEEP_DURATION:
			case CFG_CNF_HOLDOVER_DURATION:
			case CFG_CNF_OWN_DTIM_PERIOD:
			case CFG_CNF_MCAST_PM_BUF:
			case CFG_CNF_REJECT_ANY:
			case CFG_CNF_ENCRYPTION:
			case CFG_CNF_AUTHENTICATION:
			case CFG_CNF_EXCL_UNENCRYPTED:
			case CFG_CNF_INTRA_BSS_RELAY:
			case CFG_CNF_MICRO_WAVE:
			case CFG_CNF_LOAD_BALANCING:
			case CFG_CNF_MEDIUM_DISTRIBUTION:
#ifdef WARP
			case CFG_CNF_TX_POW_LVL:
			case CFG_CNF_CONNECTION_CNTL:
			case CFG_CNF_OWN_BEACON_INTERVAL:                          // Own Beacon Interval
			case CFG_COEXISTENSE_BEHAVIOUR:                            // Coexistence Behavior
			//case CFG_CNF_RX_ALL_GROUP_ADDRESS:
#endif // HERMES25
			case CFG_CREATE_IBSS:
			case CFG_RTS_THRH:
			case CFG_PROMISCUOUS_MODE:
			//case CFG_WAKE_ON_LAN:
			case CFG_RTS_THRH0:
			case CFG_RTS_THRH1:
			case CFG_RTS_THRH2:
			case CFG_RTS_THRH3:
			case CFG_RTS_THRH4:
			case CFG_RTS_THRH5:
			case CFG_RTS_THRH6:
			case CFG_TX_RATE_CNTL0:
			case CFG_TX_RATE_CNTL1:
			case CFG_TX_RATE_CNTL2:
			case CFG_TX_RATE_CNTL3:
			case CFG_TX_RATE_CNTL4:
			case CFG_TX_RATE_CNTL5:
			case CFG_TX_RATE_CNTL6:
			case CFG_TX_KEY_ID:
			case CFG_TICK_TIME:
			case CFG_MAX_LOAD_TIME:
			case CFG_NIC_TEMP_TYPE:
			case CFG_PORT_STAT:
			case CFG_CUR_TX_RATE:
			case CFG_CUR_BEACON_INTERVAL:
			case CFG_PROTOCOL_RSP_TIME:
			case CFG_CUR_SHORT_RETRY_LIMIT:
			case CFG_CUR_LONG_RETRY_LIMIT:
			case CFG_MAX_TX_LIFETIME:
			case CFG_MAX_RX_LIFETIME:
			case CFG_CF_POLLABLE:
			case CFG_PRIVACY_OPT_IMPLEMENTED:
			//case CFG_CURRENT_REMOTE_RATES:
			//case CFG_CURRENT_USED_RATES:
			//case CFG_CURRENT_SYSTEM_SCALE:
			//case CFG_CURRENT_TX_RATE1:
			//case CFG_CURRENT_TX_RATE2:
			//case CFG_CURRENT_TX_RATE3:
			//case CFG_CURRENT_TX_RATE4:
			//case CFG_CURRENT_TX_RATE5:
			//case CFG_CURRENT_TX_RATE6:
			case CFG_PHY_TYPE:
			case CFG_CUR_CHANNEL:
			//case CFG_CURRENT_POWER_STATE:
			//case CFG_CCAMODE:
			//    lp->ltvRecord.u.u16[0] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[0] );
			//    break;
			/* name string gets just need the first hcf_16 byte flipped (length of string) */
			case CFG_CNF_OWN_SSID:
			case CFG_CNF_OWN_NAME:
			//case CNF_DESIRED_SSID:
			case CFG_DESIRED_SSID:
			case CFG_SCAN_SSID:
			case CFG_CUR_SSID:
				lp->ltvRecord.u.u16[0] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[0] );
				break;
			/* non-length counted strings need no byte flipping */
			case CFG_CNF_OWN_MAC_ADDR:
			/* this case is no longer valid: CFG_CNF_WDS_ADDR */
			case CFG_CNF_WDS_ADDR1:
			case CFG_CNF_WDS_ADDR2:
			case CFG_CNF_WDS_ADDR3:
			case CFG_CNF_WDS_ADDR4:
			case CFG_CNF_WDS_ADDR5:
			case CFG_CNF_WDS_ADDR6:
			case CFG_GROUP_ADDR:
			case CFG_NIC_SERIAL_NUMBER:
			case CFG_CUR_BSSID:
			case CFG_NIC_MAC_ADDR:
			case CFG_SUPPORTED_DATA_RATES:  /* need to ensure we can treat this as a string */
				break;
			//case CFG_CNF_COUNTRY_INFO:      /* special case, see page 75  of 022486, Rev C. */
			//case CFG_CURRENT_COUNTRY_INFO:  /* special case, see page 101 of 022486, Rev C. */
			/*
				lp->ltvRecord.u.u16[0] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[0] );
				lp->ltvRecord.u.u16[3] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[3] );

				for( i = 4; i < lp->ltvRecord.len; i++ ) {
					lp->ltvRecord.u.u16[i] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[i] );
				}
				break;
			*/

			case CFG_DEFAULT_KEYS:
				{
					CFG_DEFAULT_KEYS_STRCT *pKeys = (CFG_DEFAULT_KEYS_STRCT *)&lp->ltvRecord.u.u8[0];

					pKeys[0].len = CNV_INT_TO_LITTLE( pKeys[0].len );
					pKeys[1].len = CNV_INT_TO_LITTLE( pKeys[1].len );
					pKeys[2].len = CNV_INT_TO_LITTLE( pKeys[2].len );
					pKeys[3].len = CNV_INT_TO_LITTLE( pKeys[3].len );
				}
				break;
			case CFG_CNF_MCAST_RATE:
			case CFG_TX_RATE_CNTL:
			case CFG_SUPPORTED_RATE_SET_CNTL:    // Supported Rate Set Control
			case CFG_BASIC_RATE_SET_CNTL:    // Basic Rate Set Control
				lp->ltvRecord.u.u16[0] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[0] );
				lp->ltvRecord.u.u16[1] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[1] );
				break;
			case CFG_DL_BUF:
			case CFG_NIC_IDENTITY:
			case CFG_COMMS_QUALITY:
			case CFG_PCF_INFO:
				lp->ltvRecord.u.u16[0] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[0] );
				lp->ltvRecord.u.u16[1] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[1] );
				lp->ltvRecord.u.u16[2] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[2] );
				break;
			case CFG_FW_IDENTITY:
				lp->ltvRecord.u.u16[0] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[0] );
				lp->ltvRecord.u.u16[1] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[1] );
				lp->ltvRecord.u.u16[2] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[2] );
				lp->ltvRecord.u.u16[3] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[3] );
				break;
			//case CFG_HSI_SUP_RANGE:
			case CFG_NIC_MFI_SUP_RANGE:
			case CFG_NIC_CFI_SUP_RANGE:
			case CFG_NIC_PROFILE:
			case CFG_FW_SUP_RANGE:
				lp->ltvRecord.u.u16[0] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[0] );
				lp->ltvRecord.u.u16[1] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[1] );
				lp->ltvRecord.u.u16[2] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[2] );
				lp->ltvRecord.u.u16[3] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[3] );
				lp->ltvRecord.u.u16[4] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[4] );
				break;
			case CFG_MFI_ACT_RANGES_STA:
			case CFG_CFI_ACT_RANGES_STA:
			case CFG_CUR_SCALE_THRH:
			case CFG_AUTHENTICATION_ALGORITHMS:
				for( i = 0; i < ( lp->ltvRecord.len - 1 ); i++ ) {
					lp->ltvRecord.u.u16[i] = CNV_INT_TO_LITTLE( lp->ltvRecord.u.u16[i] );
				}
				break;
			/* done at init time, and endian handled then */
			case CFG_PRI_IDENTITY:
				break;
			case CFG_MB_INFO:
				//wvlanEndianTranslateMailbox( pLtv );
				break;
			/* MSF and HCF RIDS */
			case CFG_IFB:
			case CFG_DRV_INFO:
			case CFG_AP_MODE:
			case CFG_ENCRYPT_STRING:
			case CFG_COUNTRY_STRING:
			case CFG_DRIVER_ENABLE:
			case CFG_WOLAS_ENABLE:
			default:
				break;
			}
