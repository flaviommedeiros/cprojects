static long mem_cgroup_read_stat(struct mem_cgroup *memcg,
				 enum mem_cgroup_stat_index idx)
{
	long val = 0;
	int cpu;

	get_online_cpus();
	for_each_online_cpu(cpu)
		val += per_cpu(memcg->stat->count[idx], cpu);
#ifdef CONFIG_HOTPLUG_CPU
	spin_lock(&memcg->pcp_counter_lock);
	val += memcg->nocpu_base.count[idx];
	spin_unlock(&memcg->pcp_counter_lock);
#endif
	put_online_cpus();
	return val;
}
