#ifdef CONFIG_TR
if (is_trdev)
			dev_lec[i] = alloc_trdev(size);
		else
#endif
			dev_lec[i] = alloc_etherdev(size);
