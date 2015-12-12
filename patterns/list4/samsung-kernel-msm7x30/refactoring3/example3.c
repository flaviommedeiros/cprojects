switch(name) {
		case BLKIO_PROP_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_TIME, 0, 0);
		case BLKIO_PROP_sectors:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_CPU_SECTORS, 0, 1);
		case BLKIO_PROP_io_service_bytes:
			return blkio_read_blkg_stats(blkcg, cft, cb,
					BLKIO_STAT_CPU_SERVICE_BYTES, 1, 1);
		case BLKIO_PROP_io_serviced:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_CPU_SERVICED, 1, 1);
		case BLKIO_PROP_io_service_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_SERVICE_TIME, 1, 0);
		case BLKIO_PROP_io_wait_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_WAIT_TIME, 1, 0);
		case BLKIO_PROP_io_merged:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_CPU_MERGED, 1, 1);
		case BLKIO_PROP_io_queued:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_QUEUED, 1, 0);
#ifdef CONFIG_DEBUG_BLK_CGROUP
		case BLKIO_PROP_unaccounted_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
					BLKIO_STAT_UNACCOUNTED_TIME, 0, 0);
		case BLKIO_PROP_dequeue:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_DEQUEUE, 0, 0);
		case BLKIO_PROP_avg_queue_size:
			return blkio_read_blkg_stats(blkcg, cft, cb,
					BLKIO_STAT_AVG_QUEUE_SIZE, 0, 0);
		case BLKIO_PROP_group_wait_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
					BLKIO_STAT_GROUP_WAIT_TIME, 0, 0);
		case BLKIO_PROP_idle_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_IDLE_TIME, 0, 0);
		case BLKIO_PROP_empty_time:
			return blkio_read_blkg_stats(blkcg, cft, cb,
						BLKIO_STAT_EMPTY_TIME, 0, 0);
#endif
		default:
			BUG();
		}
