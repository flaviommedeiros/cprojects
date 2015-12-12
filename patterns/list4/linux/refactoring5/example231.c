#ifdef CONFIG_NUMA
if (size * sizeof(spinlock_t) > PAGE_SIZE &&
		    gfp == GFP_KERNEL)
			tbl->locks = vmalloc(size * sizeof(spinlock_t));
		else
#endif
		tbl->locks = kmalloc_array(size, sizeof(spinlock_t),
					   gfp);
