switch (node->type) {
		/*
		 *	Don't escape this.
		 */
	case XLAT_LITERAL:
		XLAT_DEBUG("xlat_aprint LITERAL");
		return talloc_typed_strdup(ctx, node->fmt);

		/*
		 *	Do a one-character expansion.
		 */
	case XLAT_PERCENT:
	{
		char *nl;
		size_t freespace = 256;
		struct tm ts;
		time_t when;

		XLAT_DEBUG("xlat_aprint PERCENT");

		str = talloc_array(ctx, char, freespace); /* @todo do better allocation */
		p = node->fmt;

		when = request->timestamp.tv_sec;
		if (request->packet) {
			when = request->packet->timestamp.tv_sec;
		}

		switch (*p) {
		case '%':
			str[0] = '%';
			str[1] = '\0';
			break;

		case 'd': /* request day */
			if (!localtime_r(&when, &ts)) goto error;
			strftime(str, freespace, "%d", &ts);
			break;

		case 'l': /* request timestamp */
			snprintf(str, freespace, "%lu",
				 (unsigned long) when);
			break;

		case 'm': /* request month */
			if (!localtime_r(&when, &ts)) goto error;
			strftime(str, freespace, "%m", &ts);
			break;

		case 'n': /* Request Number*/
			snprintf(str, freespace, "%u", request->number);
			break;

		case 't': /* request timestamp */
			CTIME_R(&when, str, freespace);
			nl = strchr(str, '\n');
			if (nl) *nl = '\0';
			break;

		case 'D': /* request date */
			if (!localtime_r(&when, &ts)) goto error;
			strftime(str, freespace, "%Y%m%d", &ts);
			break;

		case 'G': /* request minute */
			if (!localtime_r(&when, &ts)) goto error;
			strftime(str, freespace, "%M", &ts);
			break;

		case 'H': /* request hour */
			if (!localtime_r(&when, &ts)) goto error;
			strftime(str, freespace, "%H", &ts);
			break;

		case 'I': /* Request ID */
			if (request->packet) {
				snprintf(str, freespace, "%i", request->packet->id);
			}
			break;

		case 'S': /* request timestamp in SQL format*/
			if (!localtime_r(&when, &ts)) goto error;
			strftime(str, freespace, "%Y-%m-%d %H:%M:%S", &ts);
			break;

		case 'T': /* request timestamp */
			if (!localtime_r(&when, &ts)) goto error;
			strftime(str, freespace, "%Y-%m-%d-%H.%M.%S.000000", &ts);
			break;

		case 'Y': /* request year */
			if (!localtime_r(&when, &ts)) {
				error:
				REDEBUG("Failed converting packet timestamp to localtime: %s", fr_syserror(errno));
				talloc_free(str);
				return NULL;
			}
			strftime(str, freespace, "%Y", &ts);
			break;

		case 'v': /* Version of code */
			RWDEBUG("%%v is deprecated and will be removed.  Use ${version.freeradius-server}");
			snprintf(str, freespace, "%s", radiusd_version_short);
			break;

		default:
			rad_assert(0 == 1);
			break;
		}
	}
		break;

	case XLAT_ATTRIBUTE:
		XLAT_DEBUG("xlat_aprint ATTRIBUTE");

		/*
		 *	Some attributes are virtual <sigh>
		 */
		str = xlat_getvp(ctx, request, &node->attr, escape ? false : true, true);
		if (str) {
			XLAT_DEBUG("EXPAND attr %s", node->attr.tmpl_da->name);
			XLAT_DEBUG("       ---> %s", str);
		}
		break;

	case XLAT_VIRTUAL:
		XLAT_DEBUG("xlat_aprint VIRTUAL");

		if (node->xlat->buf_len > 0) {
			str = talloc_array(request, char, node->xlat->buf_len);
			str[0] = '\0';	/* Be sure the string is \0 terminated */
		}
		rcode = node->xlat->func(&str, node->xlat->buf_len, node->xlat->mod_inst, NULL, request, NULL);
		if (rcode < 0) {
			talloc_free(str);
			return NULL;
		}
		RDEBUG2("EXPAND %s", node->xlat->name);
		RDEBUG2("   --> %s", str);
		break;

	case XLAT_MODULE:
		XLAT_DEBUG("xlat_aprint MODULE");

		if (node->child) {
			if (xlat_process(&child, request, node->child, node->xlat->escape, node->xlat->mod_inst) == 0) {
				return NULL;
			}

			XLAT_DEBUG("%.*sEXPAND mod %s %s", lvl, xlat_spaces, node->fmt, node->child->fmt);
		} else {
			XLAT_DEBUG("%.*sEXPAND mod %s", lvl, xlat_spaces, node->fmt);
			child = talloc_typed_strdup(ctx, "");
		}

		XLAT_DEBUG("%.*s      ---> %s", lvl, xlat_spaces, child);

		/*
		 *	Smash \n --> CR.
		 *
		 *	The OUTPUT of xlat is a "raw" string.  The INPUT is a printable string.
		 *
		 *	This is really the reverse of fr_snprint().
		 */
		if (*child) {
			PW_TYPE type;
			value_data_t data;

			type = PW_TYPE_STRING;
			if (value_data_from_str(request, &data, &type, NULL, child, talloc_array_length(child) - 1, '"') < 0) {
				talloc_free(child);
				return NULL;
			}

			talloc_free(child);
			child = data.ptr;

		} else {
			char *q;

			p = q = child;
			while (*p) {
				if (*p == '\\') switch (p[1]) {
					default:
						*(q++) = p[1];
						p += 2;
						continue;

					case 'n':
						*(q++) = '\n';
						p += 2;
						continue;

					case 't':
						*(q++) = '\t';
						p += 2;
						continue;
					}

				*(q++) = *(p++);
			}
			*q = '\0';
		}

		if (node->xlat->buf_len > 0) {
			str = talloc_array(request, char, node->xlat->buf_len);
			str[0] = '\0';	/* Be sure the string is \0 terminated */
		}
		rcode = node->xlat->func(&str, node->xlat->buf_len, node->xlat->mod_inst, NULL, request, child);
		talloc_free(child);
		if (rcode < 0) {
			talloc_free(str);
			return NULL;
		}
		break;

#ifdef HAVE_REGEX
	case XLAT_REGEX:
		XLAT_DEBUG("xlat_aprint REGEX");
		if (regex_request_to_sub(ctx, &str, request, node->attr.tmpl_num) < 0) return NULL;

		break;
#endif

	case XLAT_ALTERNATE:
		XLAT_DEBUG("xlat_aprint ALTERNATE");
		rad_assert(node->child != NULL);
		rad_assert(node->alternate != NULL);

		str = xlat_aprint(ctx, request, node->child, escape, escape_ctx, lvl);
		if (str) {
			XLAT_DEBUG("ALTERNATE got string: %s", str);
			break;
		}

		XLAT_DEBUG("ALTERNATE going to alternate");
		str = xlat_aprint(ctx, request, node->alternate, escape, escape_ctx, lvl);
		break;

	}
