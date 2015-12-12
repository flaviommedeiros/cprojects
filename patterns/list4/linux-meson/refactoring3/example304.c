switch (psta->dot118021XPrivacy)
					{
						case _NO_PRIVACY_:
							DBG_871X_SEL_NL(m, "%s\n", "NO PRIVACY");
							break;
						case _WEP40_:	
							DBG_871X_SEL_NL(m, "%s\n", "WEP 40");
							break;
						case _TKIP_:
							DBG_871X_SEL_NL(m, "%s\n", "TKIP");
							break;
						case _TKIP_WTMIC_:
							DBG_871X_SEL_NL(m, "%s\n", "TKIP WTMIC");
							break;
						case _AES_:				
							DBG_871X_SEL_NL(m, "%s\n", "AES");
							break;
						case _WEP104_:
							DBG_871X_SEL_NL(m, "%s\n", "WEP 104");
							break;
						case _WEP_WPA_MIXED_:
							DBG_871X_SEL_NL(m, "%s\n", "WEP/WPA Mixed");
							break;
						case _SMS4_:
							DBG_871X_SEL_NL(m, "%s\n", "SMS4");
							break;
#ifdef CONFIG_IEEE80211W
						case _BIP_:
							DBG_871X_SEL_NL(m, "%s\n", "BIP");
							break;
#endif //CONFIG_IEEE80211W
					}
