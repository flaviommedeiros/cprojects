static uint64_t blkio_get_stat(struct blkio_group *blkg,
		struct cgroup_map_cb *cb, dev_t dev, enum stat_type type)
{
	uint64_t disk_total;
	char key_str[MAX_KEY_LEN];
	enum stat_sub_type sub_type;

	if (type == BLKIO_STAT_TIME)
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1,
					blkg->stats.time, cb, dev);
#ifdef CONFIG_DEBUG_BLK_CGROUP
	if (type == BLKIO_STAT_UNACCOUNTED_TIME)
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1,
					blkg->stats.unaccounted_time, cb, dev);
	if (type == BLKIO_STAT_AVG_QUEUE_SIZE) {
		uint64_t sum = blkg->stats.avg_queue_size_sum;
		uint64_t samples = blkg->stats.avg_queue_size_samples;
		if (samples)
			do_div(sum, samples);
		else
			sum = 0;
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1, sum, cb, dev);
	}
	if (type == BLKIO_STAT_GROUP_WAIT_TIME)
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1,
					blkg->stats.group_wait_time, cb, dev);
	if (type == BLKIO_STAT_IDLE_TIME)
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1,
					blkg->stats.idle_time, cb, dev);
	if (type == BLKIO_STAT_EMPTY_TIME)
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1,
					blkg->stats.empty_time, cb, dev);
	if (type == BLKIO_STAT_DEQUEUE)
		return blkio_fill_stat(key_str, MAX_KEY_LEN - 1,
					blkg->stats.dequeue, cb, dev);
#endif

	for (sub_type = BLKIO_STAT_READ; sub_type < BLKIO_STAT_TOTAL;
			sub_type++) {
		blkio_get_key_name(sub_type, dev, key_str, MAX_KEY_LEN, false);
		cb->fill(cb, key_str, blkg->stats.stat_arr[type][sub_type]);
	}
	disk_total = blkg->stats.stat_arr[type][BLKIO_STAT_READ] +
			blkg->stats.stat_arr[type][BLKIO_STAT_WRITE];
	blkio_get_key_name(BLKIO_STAT_TOTAL, dev, key_str, MAX_KEY_LEN, false);
	cb->fill(cb, key_str, disk_total);
	return disk_total;
}
