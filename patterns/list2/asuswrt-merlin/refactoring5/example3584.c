#ifdef BTRFS_COMPAT_EXTENT_TREE_V0
if (ptr + sizeof(struct btrfs_extent_item_v0) == end)
		ptr = end;
	else
#endif
		ptr += sizeof(struct btrfs_extent_item);
