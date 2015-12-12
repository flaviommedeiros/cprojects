#ifdef RE_ENABLE_I18N
if (dfa->nodes[node].accept_mb)
	naccepted = check_node_accept_bytes (dfa, node, &mctx->input, *pidx);
      else
#endif /* RE_ENABLE_I18N */
      if (type == OP_BACK_REF)
	{
	  Idx subexp_idx = dfa->nodes[node].opr.idx + 1;
	  naccepted = regs[subexp_idx].rm_eo - regs[subexp_idx].rm_so;
	  if (fs != NULL)
	    {
	      if (regs[subexp_idx].rm_so == -1 || regs[subexp_idx].rm_eo == -1)
		return REG_MISSING;
	      else if (naccepted)
		{
		  char *buf = (char *) re_string_get_buffer (&mctx->input);
		  if (memcmp (buf + regs[subexp_idx].rm_so, buf + *pidx,
			      naccepted) != 0)
		    return REG_MISSING;
		}
	    }

	  if (naccepted == 0)
	    {
	      Idx dest_node;
	      ok = re_node_set_insert (eps_via_nodes, node);
	      if (BE (! ok, 0))
		return REG_ERROR;
	      dest_node = dfa->edests[node].elems[0];
	      if (re_node_set_contains (&mctx->state_log[*pidx]->nodes,
					dest_node))
		return dest_node;
	    }
	}
