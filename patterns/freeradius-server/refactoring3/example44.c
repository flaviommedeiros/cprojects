switch (c->type) {
		default:
			rad_assert(0 == 1);
			break;

#ifdef WITH_UNLANG
		case MOD_UPDATE:
			g = mod_callabletogroup(c);
			if (g->done_pass2) goto do_next;

			name2 = cf_section_name2(g->cs);
			if (!name2) {
				c->debug_name = unlang_keyword[c->type];
			} else {
				c->debug_name = talloc_asprintf(c, "update %s", name2);
			}

			if (!pass2_update_compile(g)) {
				return false;
			}
			g->done_pass2 = true;
			break;

		case MOD_MAP:
			g = mod_callabletogroup(c);
			if (g->done_pass2) goto do_next;

			if (!pass2_map_compile(g)) {
				return false;
			}
			g->done_pass2 = true;
			c->debug_name = c->name;
			break;

		case MOD_XLAT:   /* @todo: pre-parse xlat's */
		case MOD_REFERENCE:
		case MOD_BREAK:
		case MOD_RETURN:
#endif

		case MOD_SINGLE:
			c->debug_name = c->name;
			break;	/* do nothing */

#ifdef WITH_UNLANG
		case MOD_IF:
		case MOD_ELSIF:
			g = mod_callabletogroup(c);
			if (g->done_pass2) goto do_next;

			name2 = cf_section_name2(g->cs);
			c->debug_name = talloc_asprintf(c, "%s %s", unlang_keyword[c->type], name2);

			/*
			 *	The compilation code takes care of
			 *	simplifying 'true' and 'false'
			 *	conditions.  For others, we have to do
			 *	a second pass to parse && compile
			 *	xlats.
			 */
			if (!((g->cond->type == COND_TYPE_TRUE) ||
			      (g->cond->type == COND_TYPE_FALSE))) {
				if (!fr_condition_walk(g->cond, pass2_callback, NULL)) {
					return false;
				}
			}

			if (!modcall_pass2(g->children)) return false;
			g->done_pass2 = true;
			break;
#endif

#ifdef WITH_UNLANG
		case MOD_SWITCH:
			g = mod_callabletogroup(c);
			if (g->done_pass2) goto do_next;

			name2 = cf_section_name2(g->cs);
			c->debug_name = talloc_asprintf(c, "%s %s", unlang_keyword[c->type], name2);

			/*
			 *	We had &Foo-Bar, where Foo-Bar is
			 *	defined by a module.
			 */
			if (!g->vpt) {
				rad_assert(c->name != NULL);
				rad_assert(c->name[0] == '&');
				rad_assert(cf_section_name2_type(g->cs) == T_BARE_WORD);

				slen = tmpl_afrom_str(g->cs, &g->vpt, c->name, strlen(c->name),
						      cf_section_name2_type(g->cs),
						      REQUEST_CURRENT, PAIR_LIST_REQUEST, true);
				if (slen < 0) {
					char *spaces, *text;

				parse_error:
					fr_canonicalize_error(g->cs, &spaces, &text, slen, fr_strerror());

					cf_log_err_cs(g->cs, "Syntax error");
					cf_log_err_cs(g->cs, "%s", c->name);
					cf_log_err_cs(g->cs, "%s^ %s", spaces, text);

					talloc_free(spaces);
					talloc_free(text);

					return false;
				}

				goto do_children;
			}

			/*
			 *	Statically compile xlats
			 */
			if (g->vpt->type == TMPL_TYPE_XLAT) {
				if (!pass2_xlat_compile(cf_section_to_item(g->cs),
							&g->vpt, true, NULL)) {
					return false;
				}

				goto do_children;
			}

			/*
			 *	Convert virtual &Attr-Foo to "%{Attr-Foo}"
			 */
			if ((g->vpt->type == TMPL_TYPE_ATTR) && g->vpt->tmpl_da->flags.virtual) {
				g->vpt->tmpl_xlat = xlat_from_tmpl_attr(g->vpt, g->vpt);
				g->vpt->type = TMPL_TYPE_XLAT_STRUCT;
			}

			/*
			 *	We may have: switch Foo-Bar {
			 *
			 *	where Foo-Bar is an attribute defined
			 *	by a module.  Since there's no leading
			 *	&, it's parsed as a literal.  But if
			 *	we can parse it as an attribute,
			 *	switch to using that.
			 */
			if (g->vpt->type == TMPL_TYPE_UNPARSED) {
				vp_tmpl_t *vpt;

				slen = tmpl_afrom_str(g->cs, &vpt, c->name, strlen(c->name), cf_section_name2_type(g->cs),
						      REQUEST_CURRENT, PAIR_LIST_REQUEST, true);
				if (slen < 0) goto parse_error;
				if (vpt->type == TMPL_TYPE_ATTR) {
					talloc_free(g->vpt);
					g->vpt = vpt;
				}

				goto do_children;
			}

			/*
			 *	Warn about old-style configuration.
			 *
			 *	DEPRECATED: switch User-Name { ...
			 *	ALLOWED   : switch &User-Name { ...
			 */
			if ((g->vpt->type == TMPL_TYPE_ATTR) &&
			    (c->name[0] != '&')) {
				WARN("%s[%d]: Please change %s to &%s",
				     cf_section_filename(g->cs),
				     cf_section_lineno(g->cs),
				     c->name, c->name);
			}

		do_children:
			if (!modcall_pass2(g->children)) return false;
			g->done_pass2 = true;
			break;

		case MOD_CASE:
			g = mod_callabletogroup(c);
			if (g->done_pass2) goto do_next;

			name2 = cf_section_name2(g->cs);
			if (!name2) {
				c->debug_name = unlang_keyword[c->type];
			} else {
				c->debug_name = talloc_asprintf(c, "%s %s", unlang_keyword[c->type], name2);
			}

			rad_assert(c->parent != NULL);
			rad_assert(c->parent->type == MOD_SWITCH);

			/*
			 *	The statement may refer to an
			 *	attribute which doesn't exist until
			 *	all of the modules have been loaded.
			 *	Check for that now.
			 */
			if (!g->vpt && c->name &&
			    (c->name[0] == '&') &&
			    (cf_section_name2_type(g->cs) == T_BARE_WORD)) {
				slen = tmpl_afrom_str(g->cs, &g->vpt, c->name, strlen(c->name),
						      cf_section_name2_type(g->cs),
						      REQUEST_CURRENT, PAIR_LIST_REQUEST, true);
				if (slen < 0) goto parse_error;
			}

			/*
			 *	We have "case {...}".  There's no
			 *	argument, so we don't need to check
			 *	it.
			 */
			if (!g->vpt) goto do_children;

			/*
			 *	Do type-specific checks on the case statement
			 */
			if (g->vpt->type == TMPL_TYPE_UNPARSED) {
				modgroup *f;

				f = mod_callabletogroup(mc->parent);
				rad_assert(f->vpt != NULL);

				/*
				 *	We're switching over an
				 *	attribute.  Check that the
				 *	values match.
				 */
				if (f->vpt->type == TMPL_TYPE_ATTR) {
					rad_assert(f->vpt->tmpl_da != NULL);

					if (tmpl_cast_in_place(g->vpt, f->vpt->tmpl_da->type, f->vpt->tmpl_da) < 0) {
						cf_log_err_cs(g->cs, "Invalid argument for case statement: %s",
							      fr_strerror());
						return false;
					}
				}

				goto do_children;
			}

			/*
			 *	Compile and sanity check xlat
			 *	expansions.
			 */
			if (g->vpt->type == TMPL_TYPE_XLAT) {
				modgroup *f;

				f = mod_callabletogroup(mc->parent);
				rad_assert(f->vpt != NULL);

				/*
				 *	Don't expand xlat's into an
				 *	attribute of a different type.
				 */
				if (f->vpt->type == TMPL_TYPE_ATTR) {
					if (!pass2_xlat_compile(cf_section_to_item(g->cs),
								&g->vpt, true, f->vpt->tmpl_da)) {
						return false;
					}
				} else {
					if (!pass2_xlat_compile(cf_section_to_item(g->cs),
								&g->vpt, true, NULL)) {
						return false;
					}
				}
			}

			if (!modcall_pass2(g->children)) return false;
			g->done_pass2 = true;
			break;

		case MOD_FOREACH:
			g = mod_callabletogroup(c);
			if (g->done_pass2) goto do_next;

			name2 = cf_section_name2(g->cs);
			c->debug_name = talloc_asprintf(c, "%s %s", unlang_keyword[c->type], name2);

			/*
			 *	Already parsed, handle the children.
			 */
			if (g->vpt) goto check_children;

			/*
			 *	We had &Foo-Bar, where Foo-Bar is
			 *	defined by a module.
			 */
			rad_assert(c->name != NULL);
			rad_assert(c->name[0] == '&');
			rad_assert(cf_section_name2_type(g->cs) == T_BARE_WORD);

			/*
			 *	The statement may refer to an
			 *	attribute which doesn't exist until
			 *	all of the modules have been loaded.
			 *	Check for that now.
			 */
			slen = tmpl_afrom_str(g->cs, &g->vpt, c->name, strlen(c->name), cf_section_name2_type(g->cs),
					      REQUEST_CURRENT, PAIR_LIST_REQUEST, true);
			if (slen < 0) goto parse_error;

		check_children:
			rad_assert((g->vpt->type == TMPL_TYPE_ATTR) || (g->vpt->type == TMPL_TYPE_LIST));
			if (g->vpt->tmpl_num != NUM_ALL) {
				cf_log_err_cs(g->cs, "MUST NOT use instance selectors in 'foreach'");
				return false;
			}
			if (!modcall_pass2(g->children)) return false;
			g->done_pass2 = true;
			break;

		case MOD_ELSE:
			c->debug_name = unlang_keyword[c->type];
			goto do_recurse;

		case MOD_POLICY:
			g = mod_callabletogroup(c);
			c->debug_name = talloc_asprintf(c, "%s %s", unlang_keyword[c->type], cf_section_name1(g->cs));
			goto do_recurse;
#endif

		case MOD_GROUP:
		case MOD_LOAD_BALANCE:
		case MOD_REDUNDANT_LOAD_BALANCE:
			c->debug_name = unlang_keyword[c->type];

#ifdef WITH_UNLANG
		do_recurse:
#endif
			g = mod_callabletogroup(c);
			if (!g->cs) {
				c->debug_name = mc->name; /* for authorize, etc. */

			} else if (c->type == MOD_GROUP) { /* for Auth-Type, etc. */
				char const *name1 = cf_section_name1(g->cs);

				if (strcmp(name1, unlang_keyword[c->type]) != 0) {
					name2 = cf_section_name2(g->cs);

					if (!name2) {
						c->debug_name = name1;
					} else {
						c->debug_name = talloc_asprintf(c, "%s %s", name1, name2);
					}
				}
			}

			if (g->done_pass2) goto do_next;
			if (!modcall_pass2(g->children)) return false;
			g->done_pass2 = true;
			break;
		}
