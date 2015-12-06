#ifdef RE_ENABLE_I18N
if (dfa->nodes[node].accept_mb)
	naccepted = check_node_accept_bytes (dfa, node, &mctx->input, *pidx);
      else
#endif /* RE_ENABLE_I18N */
      if (type == OP_BACK_REF)
	{
	  int subexp_idx = dfa->nodes[node].opr.idx + 1;
	  naccepted = regs[subexp_idx].rm_eo - regs[subexp_idx].rm_so;
	  if (fs != NULL)
	    {
	      if (regs[subexp_idx].rm_so == -1 || regs[subexp_idx].rm_eo == -1)
		return -1;
	      else if (naccepted)
		{
		  char *buf = (char *) re_string_get_buffer (&mctx->input);
		  if (memcmp (buf + regs[subexp_idx].rm_so, buf + *pidx,
			      naccepted) != 0)
		    return -1;
		}
	    }

	  if (naccepted == 0)
	    {
	      int dest_node;
	      err = re_node_set_insert (eps_via_nodes, node);
	      if (BE (err < 0, 0))
		return -2;
	      dest_node = dfa->edests[node].elems[0];
	      if (re_node_set_contains (&mctx->state_log[*pidx]->nodes,
					dest_node))
		return dest_node;
	    }
	}
