#ifdef CONFIG_NUMA
if (node != -1)
		page = alloc_pages_node(node, gfp, order);
	else
#endif
		page = alloc_pages(gfp, order);
