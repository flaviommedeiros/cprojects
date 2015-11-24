if (((grub_uint32_t) (1 << sb->block_shift) != sb->block_size)
      || (sb->used_blocks > sb->num_blocks )
      || (sb->inode_size != sb->block_size)
      || (0 == sb->block_size)
#ifndef MODE_BFS
      || ((grub_uint32_t) (1 << sb->alloc_group_shift) !=
	  sb->block_per_group * sb->block_size)
      || (sb->alloc_group_count * sb->block_per_group < sb->num_blocks)
      || (grub_afs_to_cpu16 (sb->log_block.len) != sb->log_size)
      || (grub_afs_to_cpu32 (sb->valid_log_blocks) > sb->log_size)
#endif
      )
    return 0;
