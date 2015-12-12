if (tb->pos_in_item == ih_item_len(pasted)) {
		RFALSE(tb->insert_size[0] <= 0,
		       "PAP-12275: insert size must not be %d",
		       tb->insert_size[0]);
		buffer_info_init_tbS0(tb, &bi);
		leaf_paste_in_buffer(&bi, tb->item_pos,
				     tb->pos_in_item, tb->insert_size[0], body,
				     tb->zeroes_num);

		if (is_indirect_le_ih(pasted))
			set_ih_free_space(pasted, 0);

		tb->insert_size[0] = 0;
	}
#ifdef CONFIG_REISERFS_CHECK
	else if (tb->insert_size[0]) {
		print_cur_tb("12285");
		reiserfs_panic(tb->tb_sb, "PAP-12285",
		    "insert_size must be 0 (%d)", tb->insert_size[0]);
	}
#endif
