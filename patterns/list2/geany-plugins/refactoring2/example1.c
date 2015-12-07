#ifndef G_OS_UNIX
if (!pref_async_break_bugs)
#endif
	{
		BreakData bd;
		bd.stage = BG_DISCARD;
		parse_foreach(nodes, (GFunc) break_node_parse, &bd);
	}
