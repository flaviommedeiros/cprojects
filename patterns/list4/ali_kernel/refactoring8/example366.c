static inline void stat(struct kmem_cache_cpu *c, enum stat_item si)
{
#ifdef CONFIG_SLUB_STATS
	c->stat[si]++;
#endif
}
