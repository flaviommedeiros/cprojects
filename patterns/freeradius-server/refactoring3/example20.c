switch (node->type) {
		case XLAT_LITERAL:
			DEBUG("%.*sliteral --> %s", lvl, xlat_tabs, node->fmt);
			break;

		case XLAT_PERCENT:
			DEBUG("%.*spercent --> %c", lvl, xlat_tabs, node->fmt[0]);
			break;

		case XLAT_ATTRIBUTE:
			rad_assert(node->attr.tmpl_da != NULL);
			DEBUG("%.*sattribute --> %s", lvl, xlat_tabs, node->attr.tmpl_da->name);
			rad_assert(node->child == NULL);
			if ((node->attr.tmpl_tag != TAG_ANY) || (node->attr.tmpl_num != NUM_ANY)) {
				DEBUG("%.*s{", lvl, xlat_tabs);

				DEBUG("%.*sref  %d", lvl + 1, xlat_tabs, node->attr.tmpl_request);
				DEBUG("%.*slist %d", lvl + 1, xlat_tabs, node->attr.tmpl_list);

				if (node->attr.tmpl_tag != TAG_ANY) {
					DEBUG("%.*stag %d", lvl + 1, xlat_tabs, node->attr.tmpl_tag);
				}
				if (node->attr.tmpl_num != NUM_ANY) {
					if (node->attr.tmpl_num == NUM_COUNT) {
						DEBUG("%.*s[#]", lvl + 1, xlat_tabs);
					} else if (node->attr.tmpl_num == NUM_ALL) {
						DEBUG("%.*s[*]", lvl + 1, xlat_tabs);
					} else {
						DEBUG("%.*s[%d]", lvl + 1, xlat_tabs, node->attr.tmpl_num);
					}
				}

				DEBUG("%.*s}", lvl, xlat_tabs);
			}
			break;

		case XLAT_VIRTUAL:
			rad_assert(node->fmt != NULL);
			DEBUG("%.*svirtual --> %s", lvl, xlat_tabs, node->fmt);
			break;

		case XLAT_MODULE:
			rad_assert(node->xlat != NULL);
			DEBUG("%.*sxlat --> %s", lvl, xlat_tabs, node->xlat->name);
			if (node->child) {
				DEBUG("%.*s{", lvl, xlat_tabs);
				xlat_tokenize_debug(node->child, lvl + 1);
				DEBUG("%.*s}", lvl, xlat_tabs);
			}
			break;

#ifdef HAVE_REGEX
		case XLAT_REGEX:
			DEBUG("%.*sregex-var --> %d", lvl, xlat_tabs, node->attr.tmpl_num);
			break;
#endif

		case XLAT_ALTERNATE:
			DEBUG("%.*sif {", lvl, xlat_tabs);
			xlat_tokenize_debug(node->child, lvl + 1);
			DEBUG("%.*s}", lvl, xlat_tabs);
			DEBUG("%.*selse {", lvl, xlat_tabs);
			xlat_tokenize_debug(node->alternate, lvl + 1);
			DEBUG("%.*s}", lvl, xlat_tabs);
			break;
		}
