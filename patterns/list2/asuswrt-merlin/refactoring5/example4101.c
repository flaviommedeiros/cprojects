#ifdef DHCP_RFC3397
if ((value = getenv("search")) && *value) {
			char *domain, *result;
			if ((domain = getenv("domain")) && *domain &&
			    find_word(value, trim_r(domain)) == NULL) {
				result = alloca(strlen(domain) + strlen(value) + 2);
				sprintf(result, "%s %s", domain, value);
				value = result;
			}
			changed += !nvram_match(strcat_r(prefix, "domain", tmp), trim_r(value));
			nvram_set(strcat_r(prefix, "domain", tmp), trim_r(value));
		} else
#endif
		changed += nvram_set_env(strcat_r(prefix, "domain", tmp), "domain");
