static inline void stat(const struct kmem_cache *s, enum stat_item si)
{
#ifdef CONFIG_SLUB_STATS
	__this_cpu_inc(s->cpu_slab->stat[si]);
#endif
}
