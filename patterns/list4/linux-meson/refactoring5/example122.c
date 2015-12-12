#ifdef CONFIG_80211AC_VHT
if(vht_cap == _TRUE){
					snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11AC");
				}
				else
			#endif
				{
					if(ht_cap == _TRUE)
						snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11an");
					else
						snprintf(wrqu->name, IFNAMSIZ, "IEEE 802.11a");
				}
