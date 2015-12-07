if (ch == '.' /* ".ext:mime/type" */
#if ENABLE_FEATURE_HTTPD_CONFIG_WITH_SCRIPT_INTERPR
		 || (ch == '*' && buf[1] == '.') /* "*.php:/path/php" */
#endif
		) {
			char *p;
			Htaccess *cur;

			cur = xzalloc(sizeof(*cur) /* includes space for NUL */ + strlen_buf);
			strcpy(cur->before_colon, buf);
			p = cur->before_colon + (after_colon - buf);
			p[-1] = '\0';
			cur->after_colon = p;
			if (ch == '.') {
				/* .mime line: prepend to mime_a list */
				cur->next = mime_a;
				mime_a = cur;
			}
#if ENABLE_FEATURE_HTTPD_CONFIG_WITH_SCRIPT_INTERPR
			else {
				/* script interpreter line: prepend to script_i list */
				cur->next = script_i;
				script_i = cur;
			}
#endif
			continue;
		}
