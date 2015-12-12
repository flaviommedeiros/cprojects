#ifdef CONFIG_SWIOTLB
if (!swiotlb_nr_tbl())
#endif
		sg_mark_end(sg);
