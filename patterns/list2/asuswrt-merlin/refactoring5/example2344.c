#ifdef CONFIG_SWAP
if (ptr && ptr->val) {
		entry.val = ptr->val;
		page = find_get_page(&swapper_space, entry.val);
	} else
#endif
		page = find_get_page(inode->i_mapping, pgoff);
