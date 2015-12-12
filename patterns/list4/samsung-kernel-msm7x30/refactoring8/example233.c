static struct node_attr node_state_attr[] = {
	_NODE_ATTR(possible, N_POSSIBLE),
	_NODE_ATTR(online, N_ONLINE),
	_NODE_ATTR(has_normal_memory, N_NORMAL_MEMORY),
	_NODE_ATTR(has_cpu, N_CPU),
#ifdef CONFIG_HIGHMEM
	_NODE_ATTR(has_high_memory, N_HIGH_MEMORY),
#endif
};
