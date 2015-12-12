static void set_track(struct kmem_cache *s, void *object,
			enum track_item alloc, unsigned long addr)
{
	struct track *p = get_track(s, object, alloc);

	if (addr) {
#ifdef CONFIG_STACKTRACE
		struct stack_trace trace;
		int i;

		trace.nr_entries = 0;
		trace.max_entries = TRACK_ADDRS_COUNT;
		trace.entries = p->addrs;
		trace.skip = 3;
		save_stack_trace(&trace);

		/* See rant in lockdep.c */
		if (trace.nr_entries != 0 &&
		    trace.entries[trace.nr_entries - 1] == ULONG_MAX)
			trace.nr_entries--;

		for (i = trace.nr_entries; i < TRACK_ADDRS_COUNT; i++)
			p->addrs[i] = 0;
#endif
		p->addr = addr;
		p->cpu = smp_processor_id();
		p->pid = current->pid;
		p->when = jiffies;
	} else
		memset(p, 0, sizeof(struct track));
}
