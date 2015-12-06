switch (ci->type) {
		case CONF_ITEM_SECTION:
			subcs = cf_item_to_section(ci);
			subcs = cf_section_dup(new, subcs,
					       cf_section_name1(subcs), cf_section_name2(subcs),
					       copy_meta);
			if (!subcs) {
				talloc_free(new);
				return NULL;
			}
			cf_section_add(new, subcs);
			break;

		case CONF_ITEM_PAIR:
			cp = cf_pair_dup(new, cf_item_to_pair(ci));
			if (!cp) {
				talloc_free(new);
				return NULL;
			}
			cf_pair_add(new, cp);
			break;

		case CONF_ITEM_DATA: /* Skip data */
#ifdef WITH_CONF_WRITE
		case CONF_ITEM_COMMENT:
		case CONF_ITEM_INCLUDE:
#endif
			break;

		case CONF_ITEM_INVALID:
			rad_assert(0);
		}
