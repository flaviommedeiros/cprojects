#ifdef CONFIG_SLUB_DEBUG
if (flags & SO_ALL) {
		for_each_node_state(node, N_NORMAL_MEMORY) {
			struct kmem_cache_node *n = get_node(s, node);

		if (flags & SO_TOTAL)
			x = atomic_long_read(&n->total_objects);
		else if (flags & SO_OBJECTS)
			x = atomic_long_read(&n->total_objects) -
				count_partial(n, count_free);

			else
				x = atomic_long_read(&n->nr_slabs);
			total += x;
			nodes[node] += x;
		}

	} else
#endif
	if (flags & SO_PARTIAL) {
		for_each_node_state(node, N_NORMAL_MEMORY) {
			struct kmem_cache_node *n = get_node(s, node);

			if (flags & SO_TOTAL)
				x = count_partial(n, count_total);
			else if (flags & SO_OBJECTS)
				x = count_partial(n, count_inuse);
			else
				x = n->nr_partial;
			total += x;
			nodes[node] += x;
		}
	}
