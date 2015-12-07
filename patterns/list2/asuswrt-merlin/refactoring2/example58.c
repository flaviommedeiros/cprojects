#ifdef RTCONFIG_WIRELESSREPEATER
if (strcmp(wif,"sta0")&&strcmp(wif,"sta1"))
#endif
		{
			fprintf(fp, "/etc/Wireless/sh/prewifi_%s.sh\n",wif);
			fprintf(fp2, "/etc/Wireless/sh/postwifi_%s.sh\n",wif);
		}
