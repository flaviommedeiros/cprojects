if (
#ifdef COMPRESSED_CFE
		(*(unsigned long *) (ptr+0x400) == NVRAM_MAGIC) && ( *(unsigned long *) (ptr) != NVRAM_MAGIC_MAC0)
#else
		(*(unsigned long *) (ptr+0x1000) == NVRAM_MAGIC) && ( *(unsigned long *) (ptr) != NVRAM_MAGIC_MAC0)
#endif
				&& (*(unsigned long *) (ptr) != NVRAM_MAGIC_MAC1) && (*(unsigned long *) (ptr) != NVRAM_MAGIC_RDOM )
				&& (*(unsigned long *) (ptr) != NVRAM_MAGIC_ASUS )) {
			xprintf(".Download of 0x%x bytes Completed\n", copysize);
			xprintf("Write bootloader binary to FLASH (0xbfc00000)\n");
			parseflag=1;
		}
		else if ( *(unsigned long *) (ptr) == NVRAM_MAGIC_MAC0 ) {
			xprintf("Download of 0x%x bytes completed\n", copysize);
			for (i=0; i<17; i++)
				MAC0[i] = ptr[4+i];
			MAC0[i]='\0';
			/* Wait for SCODE by SJ_Yen */
			i=i+4;
			if ((ptr[i] == SCODE[0]) &&
				(ptr [i+1] == SCODE[1]) &&
				(ptr [i+2] == SCODE[2]) &&
				(ptr [i+3] == SCODE[3]) &&
				(ptr [i+4] == SCODE[4]) ) {
				for (i = 26 ; i < 34; i++) {
					secretcode[j] = ptr [i];
					j++;
				}
				secretcode[j]='\0';
				xprintf("Write secret code = %s to FLASH\n", secretcode);
				replace(bootbuf, scode, secretcode);
				nvram_set("secret_code", (int8_t *)secretcode);
				nvram_commit();
			}
			/* End Yen */

			replace(bootbuf, et0mac, MAC0);
			replace(bootbuf, il0mac, MAC0);

			xprintf("Write MAC0 = %s  to FLASH \n", MAC0);
			xprintf("set nvram: et0macaddr=%s\n", MAC0);
			nvram_set("et0macaddr", (int8_t *)MAC0);
			xprintf("set nvram: et0macaddr=%s\n", MAC0);
			nvram_set("macaddr", (int8_t *)MAC0);
			xprintf("nvram commit\n");
			nvram_commit();
			parseflag=2;
		}
		else if ( *(unsigned long *) (ptr) == NVRAM_MAGIC_RDOM ) {
			for (i=0; i<6; i++)
				RDOM[i] = ptr[4+i];
			RDOM[i] = '\0';
			replace(bootbuf, reg_dom, RDOM);
			xprintf("Write RDOM = %s  to FLASH \n", RDOM);
			nvram_set("regulation_domain", (int8_t *)RDOM);
			nvram_commit();
			parseflag=3;
		}
		else {
			parseflag=-1;
			xprintf("Download of 0x%x bytes completed\n", copysize);
			xprintf("Not valid nvram MAGIC at all !!\n");
			copysize = 0;
		}
