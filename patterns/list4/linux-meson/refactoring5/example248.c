#ifdef CONFIG_FW_LOADER_USER_HELPER
if (buf->is_paged_buf) {
		int i;
		vunmap(buf->data);
		for (i = 0; i < buf->nr_pages; i++)
			__free_page(buf->pages[i]);
		kfree(buf->pages);
	} else
#endif
		vfree(buf->data);
