switch (node->type) {
		case XLAT_LITERAL:
			strlcpy(p, node->fmt, end - p);
			p += strlen(p);
			break;

		case XLAT_PERCENT:
			p[0] = '%';
			p[1] = node->fmt[0];
			p += 2;
			break;

		case XLAT_ATTRIBUTE:
			*(p++) = '%';
			*(p++) = '{';

			if (node->attr.tmpl_request != REQUEST_CURRENT) {
				strlcpy(p, fr_int2str(request_refs, node->attr.tmpl_request, "??"), end - p);
				p += strlen(p);
				*(p++) = '.';
			}

			if ((node->attr.tmpl_request != REQUEST_CURRENT) ||
			    (node->attr.tmpl_list != PAIR_LIST_REQUEST)) {
				strlcpy(p, fr_int2str(pair_lists, node->attr.tmpl_list, "??"), end - p);
				p += strlen(p);
				*(p++) = ':';
			}

			strlcpy(p, node->attr.tmpl_da->name, end - p);
			p += strlen(p);

			if (node->attr.tmpl_tag != TAG_ANY) {
				*(p++) = ':';
				snprintf(p, end - p, "%u", node->attr.tmpl_tag);
				p += strlen(p);
			}

			if (node->attr.tmpl_num != NUM_ANY) {
				*(p++) = '[';
				switch (node->attr.tmpl_num) {
				case NUM_COUNT:
					*(p++) = '#';
					break;

				case NUM_ALL:
					*(p++) = '*';
					break;

				default:
					snprintf(p, end - p, "%i", node->attr.tmpl_num);
					p += strlen(p);
				}
				*(p++) = ']';
			}
			*(p++) = '}';
			break;
#ifdef HAVE_REGEX
		case XLAT_REGEX:
			snprintf(p, end - p, "%%{%i}", node->attr.tmpl_num);
			p += strlen(p);
			break;
#endif
		case XLAT_VIRTUAL:
			*(p++) = '%';
			*(p++) = '{';
			strlcpy(p, node->fmt, end - p);
			p += strlen(p);
			*(p++) = '}';
			break;

		case XLAT_MODULE:
			*(p++) = '%';
			*(p++) = '{';
			strlcpy(p, node->xlat->name, end - p);
			p += strlen(p);
			*(p++) = ':';
			rad_assert(node->child != NULL);
			len = xlat_snprint(p, end - p, node->child);
			p += len;
			*(p++) = '}';
			break;

		case XLAT_ALTERNATE:
			*(p++) = '%';
			*(p++) = '{';

			len = xlat_snprint(p, end - p, node->child);
			p += len;

			*(p++) = ':';
			*(p++) = '-';

			len = xlat_snprint(p, end - p, node->alternate);
			p += len;

			*(p++) = '}';
			break;
		}
