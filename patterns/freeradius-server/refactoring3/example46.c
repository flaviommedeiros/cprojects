switch (this->type) {
		default:
			break;

		case MOD_SINGLE: {
			modsingle *single = mod_callabletosingle(this);

			DEBUG("%.*s%s", depth, modcall_spaces,
				single->modinst->name);
			}
			break;

#ifdef WITH_UNLANG
		case MOD_MAP:
			g = mod_callabletogroup(this); /* FIXMAP: print option 3, too */
			DEBUG("%.*s%s %s {", depth, modcall_spaces,
			      unlang_keyword[this->type],
			      cf_section_name2(g->cs));
			goto print_map;

		case MOD_UPDATE:
			g = mod_callabletogroup(this);
			DEBUG("%.*s%s {", depth, modcall_spaces,
				unlang_keyword[this->type]);

		print_map:
			for (map = g->map; map != NULL; map = map->next) {
				map_snprint(buffer, sizeof(buffer), map);
				DEBUG("%.*s%s", depth + 1, modcall_spaces, buffer);
			}

			DEBUG("%.*s}", depth, modcall_spaces);
			break;

		case MOD_ELSE:
			g = mod_callabletogroup(this);
			DEBUG("%.*s%s {", depth, modcall_spaces,
				unlang_keyword[this->type]);
			modcall_debug(g->children, depth + 1);
			DEBUG("%.*s}", depth, modcall_spaces);
			break;

		case MOD_IF:
		case MOD_ELSIF:
			g = mod_callabletogroup(this);
			fr_cond_snprint(buffer, sizeof(buffer), g->cond);
			DEBUG("%.*s%s (%s) {", depth, modcall_spaces,
				unlang_keyword[this->type], buffer);
			modcall_debug(g->children, depth + 1);
			DEBUG("%.*s}", depth, modcall_spaces);
			break;

		case MOD_SWITCH:
		case MOD_CASE:
			g = mod_callabletogroup(this);
			tmpl_snprint(buffer, sizeof(buffer), g->vpt, NULL);
			DEBUG("%.*s%s %s {", depth, modcall_spaces,
				unlang_keyword[this->type], buffer);
			modcall_debug(g->children, depth + 1);
			DEBUG("%.*s}", depth, modcall_spaces);
			break;

		case MOD_POLICY:
		case MOD_FOREACH:
			g = mod_callabletogroup(this);
			DEBUG("%.*s%s %s {", depth, modcall_spaces,
				unlang_keyword[this->type], this->name);
			modcall_debug(g->children, depth + 1);
			DEBUG("%.*s}", depth, modcall_spaces);
			break;

		case MOD_BREAK:
			DEBUG("%.*sbreak", depth, modcall_spaces);
			break;

#endif
		case MOD_GROUP:
			g = mod_callabletogroup(this);
			DEBUG("%.*s%s {", depth, modcall_spaces,
			      unlang_keyword[this->type]);
			modcall_debug(g->children, depth + 1);
			DEBUG("%.*s}", depth, modcall_spaces);
			break;


		case MOD_LOAD_BALANCE:
		case MOD_REDUNDANT_LOAD_BALANCE:
			g = mod_callabletogroup(this);
			DEBUG("%.*s%s {", depth, modcall_spaces,
				unlang_keyword[this->type]);
			modcall_debug(g->children, depth + 1);
			DEBUG("%.*s}", depth, modcall_spaces);
			break;
		}
