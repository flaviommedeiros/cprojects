static int dmx_ts_feed_set(struct dmx_ts_feed *ts_feed, u16 pid, int ts_type,
			   enum dmx_ts_pes pes_type,
			   size_t circular_buffer_size, struct timespec timeout)
{
	struct dvb_demux_feed *feed = (struct dvb_demux_feed *)ts_feed;
	struct dvb_demux *demux = feed->demux;

	if (pid > DMX_MAX_PID)
		return -EINVAL;

	if (mutex_lock_interruptible(&demux->mutex))
		return -ERESTARTSYS;

	if (ts_type & TS_DECODER) {
		if (pes_type >= DMX_PES_OTHER) {
			mutex_unlock(&demux->mutex);
			return -EINVAL;
		}

		if (demux->pesfilter[pes_type] &&
		    demux->pesfilter[pes_type] != feed) {
			mutex_unlock(&demux->mutex);
			return -EINVAL;
		}

		demux->pesfilter[pes_type] = feed;
		demux->pids[pes_type] = pid;
	}

	dvb_demux_feed_add(feed);

	feed->pid = pid;
	feed->buffer_size = circular_buffer_size;
	feed->timeout = timeout;
	feed->ts_type = ts_type;
	feed->pes_type = pes_type;

	if (feed->buffer_size) {
#ifdef NOBUFS
		feed->buffer = NULL;
#else
		feed->buffer = vmalloc(feed->buffer_size);
		if (!feed->buffer) {
			mutex_unlock(&demux->mutex);
			return -ENOMEM;
		}
#endif
	}

	feed->state = DMX_STATE_READY;
	mutex_unlock(&demux->mutex);

	return 0;
}
