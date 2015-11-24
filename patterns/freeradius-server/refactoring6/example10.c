if ((c->type == MOD_GROUP) || (c->type == MOD_POLICY)
#ifdef WITH_UNLANG
	    || (c->type == MOD_CASE)
#endif
		) {
		modgroup *g;

#ifdef WITH_UNLANG
	do_children:
#endif
		g = mod_callabletogroup(c);

		/*
		 *	This should really have been caught in the
		 *	compiler, and the node never generated.  But
		 *	doing that requires changing it's API so that
		 *	it returns a flag instead of the compiled
		 *	MOD_GROUP.
		 */
		if (!g->children) {
			if (c->type == MOD_CASE) {
				result = RLM_MODULE_NOOP;
				goto calculate_result;
			}

			RDEBUG2("%s { ... } # empty sub-section is ignored", c->name);
			goto next_sibling;
		}

		MOD_LOG_OPEN_BRACE;
		modcall_child(request, component,
			      depth + 1, entry, g->children,
			      &result, true);
		MOD_LOG_CLOSE_BRACE;
		goto calculate_result;
	}
