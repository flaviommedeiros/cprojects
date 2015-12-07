#ifdef BTRFS_COMPAT_EXTENT_TREE_V0
if (key.type == BTRFS_SHARED_BLOCK_REF_KEY ||
		    key.type == BTRFS_EXTENT_REF_V0_KEY) {
			if (key.type == BTRFS_EXTENT_REF_V0_KEY) {
				struct btrfs_extent_ref_v0 *ref0;
				ref0 = btrfs_item_ptr(eb, path1->slots[0],
						struct btrfs_extent_ref_v0);
				if (key.objectid == key.offset) {
					root = find_tree_root(rc, eb, ref0);
					if (root && !should_ignore_root(root))
						cur->root = root;
					else
						list_add(&cur->list, &useless);
					break;
				}
				if (is_cowonly_root(btrfs_ref_root_v0(eb,
								      ref0)))
					cur->cowonly = 1;
			}
#else
		BUG_ON(key.type == BTRFS_EXTENT_REF_V0_KEY);
		if (key.type == BTRFS_SHARED_BLOCK_REF_KEY) {
#endif
			if (key.objectid == key.offset) {
				/*
				 * only root blocks of reloc trees use
				 * backref of this type.
				 */
				root = find_reloc_root(rc, cur->bytenr);
				BUG_ON(!root);
				cur->root = root;
				break;
			}

			edge = alloc_backref_edge(cache);
			if (!edge) {
				err = -ENOMEM;
				goto out;
			}
			rb_node = tree_search(&cache->rb_root, key.offset);
			if (!rb_node) {
				upper = alloc_backref_node(cache);
				if (!upper) {
					free_backref_edge(cache, edge);
					err = -ENOMEM;
					goto out;
				}
				upper->bytenr = key.offset;
				upper->level = cur->level + 1;
				/*
				 *  backrefs for the upper level block isn't
				 *  cached, add the block to pending list
				 */
				list_add_tail(&edge->list[UPPER], &list);
			} else {
				upper = rb_entry(rb_node, struct backref_node,
						 rb_node);
				BUG_ON(!upper->checked);
				INIT_LIST_HEAD(&edge->list[UPPER]);
			}
			list_add_tail(&edge->list[LOWER], &cur->upper);
			edge->node[LOWER] = cur;
			edge->node[UPPER] = upper;

			goto next;
		} else if (key.type != BTRFS_TREE_BLOCK_REF_KEY) {
			goto next;
		}

		/* key.type == BTRFS_TREE_BLOCK_REF_KEY */
		root = read_fs_root(rc->extent_root->fs_info, key.offset);
		if (IS_ERR(root)) {
			err = PTR_ERR(root);
			goto out;
		}

		if (!root->ref_cows)
			cur->cowonly = 1;

		if (btrfs_root_level(&root->root_item) == cur->level) {
			/* tree root */
			BUG_ON(btrfs_root_bytenr(&root->root_item) !=
			       cur->bytenr);
			if (should_ignore_root(root))
				list_add(&cur->list, &useless);
			else
				cur->root = root;
			break;
		}

		level = cur->level + 1;

		/*
		 * searching the tree to find upper level blocks
		 * reference the block.
		 */
		path2->search_commit_root = 1;
		path2->skip_locking = 1;
		path2->lowest_level = level;
		ret = btrfs_search_slot(NULL, root, node_key, path2, 0, 0);
		path2->lowest_level = 0;
		if (ret < 0) {
			err = ret;
			goto out;
		}
		if (ret > 0 && path2->slots[level] > 0)
			path2->slots[level]--;

		eb = path2->nodes[level];
		WARN_ON(btrfs_node_blockptr(eb, path2->slots[level]) !=
			cur->bytenr);

		lower = cur;
		for (; level < BTRFS_MAX_LEVEL; level++) {
			if (!path2->nodes[level]) {
				BUG_ON(btrfs_root_bytenr(&root->root_item) !=
				       lower->bytenr);
				if (should_ignore_root(root))
					list_add(&lower->list, &useless);
				else
					lower->root = root;
				break;
			}

			edge = alloc_backref_edge(cache);
			if (!edge) {
				err = -ENOMEM;
				goto out;
			}

			eb = path2->nodes[level];
			rb_node = tree_search(&cache->rb_root, eb->start);
			if (!rb_node) {
				upper = alloc_backref_node(cache);
				if (!upper) {
					free_backref_edge(cache, edge);
					err = -ENOMEM;
					goto out;
				}
				upper->bytenr = eb->start;
				upper->owner = btrfs_header_owner(eb);
				upper->level = lower->level + 1;
				if (!root->ref_cows)
					upper->cowonly = 1;

				/*
				 * if we know the block isn't shared
				 * we can void checking its backrefs.
				 */
				if (btrfs_block_can_be_shared(root, eb))
					upper->checked = 0;
				else
					upper->checked = 1;

				/*
				 * add the block to pending list if we
				 * need check its backrefs. only block
				 * at 'cur->level + 1' is added to the
				 * tail of pending list. this guarantees
				 * we check backrefs from lower level
				 * blocks to upper level blocks.
				 */
				if (!upper->checked &&
				    level == cur->level + 1) {
					list_add_tail(&edge->list[UPPER],
						      &list);
				} else
					INIT_LIST_HEAD(&edge->list[UPPER]);
			} else {
				upper = rb_entry(rb_node, struct backref_node,
						 rb_node);
				BUG_ON(!upper->checked);
				INIT_LIST_HEAD(&edge->list[UPPER]);
				if (!upper->owner)
					upper->owner = btrfs_header_owner(eb);
			}
			list_add_tail(&edge->list[LOWER], &lower->upper);
			edge->node[LOWER] = lower;
			edge->node[UPPER] = upper;

			if (rb_node)
				break;
			lower = upper;
			upper = NULL;
		}
		btrfs_release_path(root, path2);
next:
		if (ptr < end) {
			ptr += btrfs_extent_inline_ref_size(key.type);
			if (ptr >= end) {
				WARN_ON(ptr > end);
				ptr = 0;
				end = 0;
			}
		}
		if (ptr >= end)
			path1->slots[0]++;
	}
