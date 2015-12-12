#ifdef __APPLE__
if (strncmp(name, "wlt", 3) == 0) {
			char *en_name;
			size_t en_name_len;

			/*
			 * Try to allocate a buffer for the "en"
			 * device's name.
			 */
			en_name_len = strlen(name) - 1;
			en_name = malloc(en_name_len + 1);
			if (en_name == NULL) {
				(void)pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
				    "malloc: %s", pcap_strerror(errno));
				return (-1);
			}
			strcpy(en_name, "en");
			strcat(en_name, name + 3);
			p = pcap_create(en_name, open_errbuf);
			free(en_name);
		} else
#endif /* __APPLE */
		p = pcap_create(name, open_errbuf);
