#ifdef CONFIG_BTRFS_FS_RUN_SANITY_TESTS
if (trans && likely(trans->type != __TRANS_DUMMY) &&
	    time_seq != (u64)-1) {
#else
	if (trans && time_seq != (u64)-1) {
#endif
		/*
		 * look if there are updates for this ref queued and lock the
		 * head
		 */
		delayed_refs = &trans->transaction->delayed_refs;
		spin_lock(&delayed_refs->lock);
		head = btrfs_find_delayed_ref_head(trans, bytenr);
		if (head) {
			if (!mutex_trylock(&head->mutex)) {
				atomic_inc(&head->node.refs);
				spin_unlock(&delayed_refs->lock);

				btrfs_release_path(path);

				/*
				 * Mutex was contended, block until it's
				 * released and try again
				 */
				mutex_lock(&head->mutex);
				mutex_unlock(&head->mutex);
				btrfs_put_delayed_ref(&head->node);
				goto again;
			}
			spin_unlock(&delayed_refs->lock);
			ret = __add_delayed_refs(head, time_seq,
						 &prefs_delayed, &total_refs,
						 inum);
			mutex_unlock(&head->mutex);
			if (ret)
				goto out;
		} else {
			spin_unlock(&delayed_refs->lock);
		}
	}

	if (path->slots[0]) {
		struct extent_buffer *leaf;
		int slot;

		path->slots[0]--;
		leaf = path->nodes[0];
		slot = path->slots[0];
		btrfs_item_key_to_cpu(leaf, &key, slot);
		if (key.objectid == bytenr &&
		    (key.type == BTRFS_EXTENT_ITEM_KEY ||
		     key.type == BTRFS_METADATA_ITEM_KEY)) {
			ret = __add_inline_refs(fs_info, path, bytenr,
						&info_level, &prefs,
						&total_refs, inum);
			if (ret)
				goto out;
			ret = __add_keyed_refs(fs_info, path, bytenr,
					       info_level, &prefs, inum);
			if (ret)
				goto out;
		}
	}
	btrfs_release_path(path);

	list_splice_init(&prefs_delayed, &prefs);

	ret = __add_missing_keys(fs_info, &prefs);
	if (ret)
		goto out;

	__merge_refs(&prefs, 1);

	ret = __resolve_indirect_refs(fs_info, path, time_seq, &prefs,
				      extent_item_pos, total_refs,
				      root_objectid);
	if (ret)
		goto out;

	__merge_refs(&prefs, 2);

	while (!list_empty(&prefs)) {
		ref = list_first_entry(&prefs, struct __prelim_ref, list);
		WARN_ON(ref->count < 0);
		if (roots && ref->count && ref->root_id && ref->parent == 0) {
			if (root_objectid && ref->root_id != root_objectid) {
				ret = BACKREF_FOUND_SHARED;
				goto out;
			}

			/* no parent == root of tree */
			ret = ulist_add(roots, ref->root_id, 0, GFP_NOFS);
			if (ret < 0)
				goto out;
		}
		if (ref->count && ref->parent) {
			if (extent_item_pos && !ref->inode_list &&
			    ref->level == 0) {
				struct extent_buffer *eb;

				eb = read_tree_block(fs_info->extent_root,
							   ref->parent, 0);
				if (IS_ERR(eb)) {
					ret = PTR_ERR(eb);
					goto out;
				} else if (!extent_buffer_uptodate(eb)) {
					free_extent_buffer(eb);
					ret = -EIO;
					goto out;
				}
				btrfs_tree_read_lock(eb);
				btrfs_set_lock_blocking_rw(eb, BTRFS_READ_LOCK);
				ret = find_extent_in_eb(eb, bytenr,
							*extent_item_pos, &eie);
				btrfs_tree_read_unlock_blocking(eb);
				free_extent_buffer(eb);
				if (ret < 0)
					goto out;
				ref->inode_list = eie;
			}
			ret = ulist_add_merge_ptr(refs, ref->parent,
						  ref->inode_list,
						  (void **)&eie, GFP_NOFS);
			if (ret < 0)
				goto out;
			if (!ret && extent_item_pos) {
				/*
				 * we've recorded that parent, so we must extend
				 * its inode list here
				 */
				BUG_ON(!eie);
				while (eie->next)
					eie = eie->next;
				eie->next = ref->inode_list;
			}
			eie = NULL;
		}
		list_del(&ref->list);
		kmem_cache_free(btrfs_prelim_ref_cache, ref);
	}

out:
	btrfs_free_path(path);
	while (!list_empty(&prefs)) {
		ref = list_first_entry(&prefs, struct __prelim_ref, list);
		list_del(&ref->list);
		kmem_cache_free(btrfs_prelim_ref_cache, ref);
	}
	while (!list_empty(&prefs_delayed)) {
		ref = list_first_entry(&prefs_delayed, struct __prelim_ref,
				       list);
		list_del(&ref->list);
		kmem_cache_free(btrfs_prelim_ref_cache, ref);
	}
	if (ret < 0)
		free_inode_elem_list(eie);
	return ret;
}
