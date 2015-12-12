static unsigned long mem_cgroup_read_events(struct mem_cgroup *memcg,
					    enum mem_cgroup_events_index idx)
{
	unsigned long val = 0;
	int cpu;

	for_each_online_cpu(cpu)
		val += per_cpu(memcg->stat->events[idx], cpu);
#ifdef CONFIG_HOTPLUG_CPU
	spin_lock(&memcg->pcp_counter_lock);
	val += memcg->nocpu_base.events[idx];
	spin_unlock(&memcg->pcp_counter_lock);
#endif
	return val;
}
