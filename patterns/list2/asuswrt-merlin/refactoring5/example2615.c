#ifdef RTCONFIG_RALINK_DFS
if(band && IEEE80211H)
					fprintf(fp, "AutoChannelSelect=%d\n", 1);			//NEED rule 1 for DFS
				else
#endif	/* RTCONFIG_RALINK_DFS */
				fprintf(fp, "AutoChannelSelect=%d\n", 2);
